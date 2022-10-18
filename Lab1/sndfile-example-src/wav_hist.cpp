#include <iostream>
#include <vector>
#include <sndfile.hh>
#include "wav_hist.h"

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536;

int main(int argc, char *argv[]){

	SndfileHandle sndFile{argv[1]};
	
	if (argc != 3){
		cerr << "Usage: " << argv[0] << " <input_wav> <channel> (where midChannel = 0 and sideChannel = 1)\n";
		return 1;
	}
	if (sndFile.error()){
		cerr << "Error: invalid input file\n";
		return 1;
	}
	if ((sndFile.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV){
		cerr << "Error: file is not in WAV format\n";
		return 1;
	}
	if ((sndFile.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16){
		cerr << "Error: file is not in PCM_16 format\n";
		return 1;
	}
	int channel{stoi(argv[2])};
	if(channel >= sndFile.channels()) {
		cerr << "Error: invalid channel requested\n";
		return 1;
	}

	size_t nFrames;
	vector<short> samples (FRAMES_BUFFER_SIZE * sndFile.channels());
	WAVHist histograma {sndFile};
	while ((nFrames = sndFile.readf(samples.data(), FRAMES_BUFFER_SIZE))){
		samples.resize(FRAMES_BUFFER_SIZE * sndFile.channels()); 
		histograma.update(samples);
	}

	if (channel == 0) {
		histograma.midD();
	} else if (channel == 1) {
		histograma.sideD();
	} else {
		histograma.dump(size_t(channel));
	}

	return 0;
}
