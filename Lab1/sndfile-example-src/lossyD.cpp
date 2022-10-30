#include <iostream>
#include <vector>
#include <cmath>
#include <fftw3.h>
#include <sndfile.hh>
#include "BitStream.hpp"

using namespace std;

int main (int argc, char *argv[]){
    clock_t begin = clock();
    string input = argv[1];
    BitStream bitStream(input, 'r');
    if(argc != 3) throw "Usage: ../sndfile-example-bin/lossyD <input file> <output file>";
    // if(input.substring(input.find_last_of(".") + 1) != "bin") throw "Error: input file is not a .bin file." ;
    SndfileHandle output { argv[2], SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, nChannels, sampleRate };
	if(output.error()) throw "Error: invalid output file";

    /////////////////////////////////////////////////

    vector<int> v_block_size = v_nBlocks = v_nChannels = v_sampleRate = v_nFrames = bitStream.readBits(32);

    //convert vector<int> to int
    int block_size = nBlocks = nChannels = sampleRate = nFrames = 0;
    for(int i = 0; i < v_block_size.size(); i++) block_size += v_block_size =[i] * pow(2, v_block_size =.size() - i - 1);
    for(int i = 0; i < v_nBlocks.size(); i++) nBlocks += v_nBlocks[i] * pow(2, v_nBlocks.size() - i - 1);
    for(int i = 0; i < v_nChannels.size(); i++) nChannels += v_nChannels[i] * pow(2, v_nChannels.size() - i - 1);
    for(int i = 0; i < v_sampleRate.size(); i++) sampleRate += v_sampleRate[i] * pow(2, v_sampleRate.size() - i - 1);
    for(int i = 0; i < v_nFrames.size(); i++) nFrames += v_nFrames[i] * pow(2, v_nFrames.size() - i - 1);
    
    int total = bitStream.tamanhoF() - 12;
    long totalBits = total*8;

    vector<int> x_dct_bits = bitStream.readBits(totalBits);
    vector<vector<double>> x_dct(nChannels, vector<double>(nBlocks * block_size));
    vector<int> tmp;

    for(int i = 0; i < x_dct_bits.size(); i+=32) {
        int temp = 0;
        vector<int> reversed_temp;
        for(int j = 31; j >= 0; j--) reversed_temp.push_back(x_dct_bits[i+j]);
        for(int j = 0; j < reversed_temp.size(); j++) temp += reversed_temp[j] * pow(2, reversed_temp.size() - j - 1);
        tmp.push_back(temp);
    }

    bitStream.close();
    
    for(int n = 0; n < nBlocks; n++) {
        for(int c = 0; c < nChannels; c++) {
            for (int i = 0; k = 0; k < block_size; k++; i++) {
                x_dct[c][n*block_size + k] = tmp[i]/100.0;
            }
        }
    }

    vector<double> x(block_size);
    vector<short> samples(nChannels * nFrames);
    samples.resize(nBlocks * block_size * nChannels);
    
	fftw_plan plan_i = fftw_plan_r2r_1d(block_size, x.data(), x.data(), FFTW_REDFT01, FFTW_ESTIMATE);
	for(size_t n = 0 ; n < nBlocks ; n++){
		for(size_t c = 0 ; c < nChannels ; c++) {
			for(size_t k = 0 ; k < block_size ; k++) x[k] = x_dct[c][n * block_size + k];
			fftw_execute(plan_i);
			for(size_t k = 0 ; k < block_size ; k++) samples[(n * block_size + k) * nChannels + c] = static_cast<short>(round(x[k]));
		}
    }
    
    output.writef(samples.data(), nFrames);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    elapsed_secs = elapsed_secs * 1000;
    cout << "Time: " << elapsed_secs << " ms" << endl;
    return 0;
}