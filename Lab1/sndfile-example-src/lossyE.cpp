#include <iostream>
#include <vector>
#include <cmath>
#include <fftw3.h>
#include <sndfile.hh>
#include "BitStream.hpp"

using namespace std;

int main (int argc, char *argv[]){
    clock_t begin = clock();

    size_t block_size { 1024 };
    size_t discarded_units_per_block { 8 };

    SndfileHandle input { argv[1] };
    string outputFileName = argv[2];
    block_size = atoi(argv[3]);
    discarded_units_per_block = atoi(argv[4]);

    if(argc != 5) throw "Usage: ../sndfile-example-bin/encoder <input file> <output file> <block_size> <discarded_units_per_block>";
    if(input.error()) throw "Error: could not open input file." ;
    if((input.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) throw "Error: input file is not a WAV file." ;
    if((input.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) throw "Error: input file is not a PCM_16 file." ;
    if(discarded_units_per_block > block_size) throw "Error: <discarded_units_per_block> must be less than block_size";

    ////////////////////////////////////////////////////////////
    size_t nChannels { static_cast<size_t>(input.channels()) };
	size_t nFrames { static_cast<size_t>(input.frames()) };

    vector<short> samples(nChannels * nFrames);
	input.readf(samples.data(), nFrames);

	size_t nBlocks { static_cast<size_t>(ceil(static_cast<double>(nFrames) / block_size)) };
	samples.resize(nBlocks * block_size * nChannels);    
	vector<vector<double>> x_dct(nChannels, vector<double>(nBlocks * block_size));
	vector<double> x(block_size);

	fftw_plan plan_d = fftw_plan_r2r_1d(block_size, x.data(), x.data(), FFTW_REDFT10, FFTW_ESTIMATE);
	for(size_t n = 0 ; n < nBlocks ; n++){
		for(size_t c = 0 ; c < nChannels ; c++) {
			for(size_t k = 0 ; k < block_size ; k++)
				x[k] = samples[(n * block_size + k) * nChannels + c];
			fftw_execute(plan_d);
			for(size_t k = 0 ; k < block_size - discarded_units_per_block ; k++)
				x_dct[c][n * block_size + k] = x[k] / (block_size << 1) * 100;
		}
    }
    BitStream outputFile (outputFileName, 'w') ;
    
    vector<int> bits;     
    for (int i = 15; i >= 0; i--) {
        bits.push_back((block_size >> i) & 1);
        bits.push_back((nBlocks >> i) & 1);
        bits.push_back((nChannels >> i) & 1);
        bits.push_back((input.samplerate() >> i)& 1);
        bits.push_back((nFrames >> i) & 1);
    }


    int value = 0;
    vector<int>values;
    //all the next bits are x_dct converted to binary
    for(size_t n = 0 ; n < nBlocks ; n++){
		for(size_t c = 0 ; c < nChannels ; c++){ 
			for(size_t k = 0 ; k < block_size ; k++){
                int tmp2 = x_dct[c][n * block_size + k];
				values.push_back(tmp2);
            }
        }
    }

    int count = 0;
    for(size_t n = 0 ; n < values.size() ; n++){
        vector<int> temp_array (32);
        vector<int> temp_array2 (32);
        for (int i = 31; i >= 0; i--) temp_array[i] = (values[n] >> i) & 1;
        for (int i = 0; i < 32; i++) temp_array2[i] = temp_array[31-i];
        for (int i = 31; i >=0; i--) bits.push_back(temp_array2[i]);
    }

    outputFile.writeBits(bits);
    outputFile.close();

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    elapsed_secs = elapsed_secs * 1000;
    cout << "Time: " << elapsed_secs << " ms" << endl;
    
    return 0;
    
}