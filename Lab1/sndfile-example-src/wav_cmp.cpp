#include <iostream>
#include <vector>
#include <sndfile.hh>
#include <audiofile.h>
#include <cmath>

int main(int argc, char *argv[]) {

	if(argc < 3) {
		cerr << "Usage: " << argv[0] << " <input file1> <input file2>\\n";
		return 1;
	}

	SndfileHandle sfhIn1 { argv[argc-2] };
	if(sfhIn1.error()) {
		cerr << "Error: invalid input file1\n";
		return 1;
    }

    SndfileHandle sfhIn2 { argv[argc-1] };
	if(sfhIn2.error()) {
		cerr << "Error: invalid input file2\n";
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

    double snr = 10 * log10(r/x);  // ruido/normal
    cout << "SNR" << snr << "dB\nMax per sample" << errM << endl;

    return 0;

}
