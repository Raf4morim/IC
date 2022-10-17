#include <iostream>
#include <vector>
#include <sndfile.hh>
#include <cmath>

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536;

int main(int argc, char **argv) {
  SndfileHandle input1 { argv[1] };
  SndfileHandle input2 { argv[2] };

  if(argc != 3) {
    cerr << "Usage: " << argv[0] << " <input1_wav> <inputQuant_wav>" << endl;
    return 1;
  }
  if(input1.error() || input2.error()) {
    cerr << "Error opening one of the files" << endl;
    return 1;
  }
  if((input1.samplerate() * input1.channels()) != (input2.samplerate() * input2.channels())) {
    cerr << "Input files have different sample rate" << endl;
    return 1;
  }
  if((input1.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
    cerr << "Input file1 " << argv[1] << " is not a WAV file" << endl;
    return 1;
  }
  if((input2.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
    cerr << "Input file2 " << argv[2] << " is not a WAV file" << endl;
    return 1;
  }

  if((input1.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
    cerr << "Input file1 " << argv[1] << " is not a 16-bit PCM WAV file" << endl;
    return 1;
  }
  if((input2.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
    cerr << "Input file2 " << argv[2] << " is not a 16-bit PCM WAV file" << endl;
    return 1;
  }
  if(input1.channels() != input2.channels()) {
    cerr << "Input files have different number of channels" << endl;
    return 1;
  }

  vector <double> origFile(FRAMES_BUFFER_SIZE * input1.channels());
  vector <double> quantFile(FRAMES_BUFFER_SIZE * input2.channels());

  size_t  n_frames_origFile;
  size_t  n_frames_quantFile;

  double errTempor, errM = 0;
  
  double totalSamples = input1.samplerate() * input1.channels();
  double x = 0,  r = 0; // energia, ruido
  double snr;
  while(n_frames_origFile = input1.readf(origFile.data(), FRAMES_BUFFER_SIZE), n_frames_quantFile = input2.readf(quantFile.data(), FRAMES_BUFFER_SIZE)) {
    origFile.resize(n_frames_origFile * input1.channels());
    quantFile.resize(n_frames_origFile * input2.channels());
    // Percorrer a matriz td de samples
    for(int i = 0; i < int(origFile.size()); i++){
        x += pow(abs(origFile[i]), 2); 
        errTempor = abs(origFile[i] - quantFile[i]);
        r += pow(errTempor, 2);
        if(errTempor > errM) errM = errTempor;
    }
  }
  x = 1/totalSamples * x;
  r = 1/totalSamples * r;

  snr = 10 * log10(r/x);  // signal-to-noise = ruido/normal
  cout << "SNR: " << snr << endl;
  cout << "Max per sample: " << errM << endl;

  return 0;

}
