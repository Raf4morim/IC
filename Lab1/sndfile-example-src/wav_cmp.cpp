#include <iostream>
#include <vector>
#include <sndfile.hh>
#include <cmath>

#include "AudioFile.h"
using namespace std;

int main(int argc, char *argv[]) {
  AudioFile<double> origFile;

  if(argc != 2) {
    cerr << "Usage: " << argv[0] << " <input1> <input2>" << endl;
    return 1;
  }
  SndfileHandle input1 { argv[argc-2] };
  if(input1.error()) {
    cerr << "Error opening input file " << argv[argc-2] << endl;
    return 1;
  }

  if((input1.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
    cerr << "Input file " << argv[argc-2] << " is not a WAV file" << endl;
    return 1;
 }

  if((input1.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
    cerr << "Input file " << argv[argc-2] << " is not a 16-bit PCM WAV file" << endl;
    return 1;
  }

  SndfileHandle input2 { argv[argc-1] };
  if(input2.error()) {
    cerr << "Error opening input file " << argv[argc-1] << endl;
    return 1;
  }

  if((input2.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
    cerr << "Input file " << argv[argc-1] << " is not a WAV file" << endl;
    return 1;
  }

  if((input2.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
    cerr << "Input file " << argv[argc-1] << " is not a 16-bit PCM WAV file" << endl;
    return 1;
  }

  if(origFile.getNumChannels() * origFile.getNumSamplesPerChannel() != quantFile.getNumChannels() * quantFile.getNumSamplesPerChannel() ){
    cerr << "Error: Same number of samples in both files\n";
    return 1;
  }

  double errTempor, errM = 0;
  int nCh = origFile.getNumChannels();
  int nSam = origFile.getNumSamplesPerChannels();

  double totalSam = (double)origFile.getNumChannels() * (double)origFile.getNumSamplesPerChannel();
  // Ruido, distorção
  double x = 0,  r = 0;
  // Percorrer a matriz td de samples
  for(int i = 0; i < nCh; i++){
    for(int j = 0; j < nCh; j++){
      x += pow(abs(origFile.samples[i][j]), 2); 
      errTempor = abs(origFile.samples[i][j] - quantFile.samples[i][j]);
      r += pow(errTempor, 2);
      if(errTempor > errM) errM = errTempor;
    }
  }
  x = 1/totalSam * x;
  r = 1/totalSam * r;

  double snr = 10 * log10(r/x);  // signal-to-noise = ruido/normal
  cout << "SNR" << snr << "dB\nMax per sample" << errM << endl;

  return 0;

}
