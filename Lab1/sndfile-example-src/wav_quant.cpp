#include <iostream>
#include <sndfile.hh>
#include <vector>
#include "wav_quant.h"

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536;

int main(int argc, char** argv) {
    if(argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_wav> <n_bits> <output_wav>" << endl;
        return 1;
    }

    SndfileHandle input { argv[argc-3] };
    if(input.error()) {
        cerr << "Error opening input file " << argv[argc-3] << endl;
        return 1;
    }

    if((input.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
        cerr << "Input file " << argv[argc-3] << " is not a WAV file" << endl;
        return 1;
    }

    if((input.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
        cerr << "Input file " << argv[argc-3] << " is not a 16-bit PCM WAV file" << endl;
        return 1;
    }


    SndfileHandle output { argv[argc-1], SFM_WRITE, input.format(), input.channels(), input.samplerate() };
    if(output.error()) {
        cerr << "Error opening output file " << argv[argc-1] << endl;
        return 1;
    }

    int n_bits = stoi(argv[argc-2]);
    if(n_bits < 1 || n_bits > 16) {
        cerr << "Invalid number of bits: " << n_bits << endl;
        return 1;
    }

    size_t n_frames { };
    vector<short> samples(FRAMES_BUFFER_SIZE * input.channels());

    WAVQuant quantizer { FRAMES_BUFFER_SIZE, n_bits };

    while((n_frames = input.readf(samples.data(), FRAMES_BUFFER_SIZE)) > 0) {
        quantizer.update(samples, n_bits);
        output.writef(samples.data(), n_frames);
    }

    return 0;






}

