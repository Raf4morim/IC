#include <iostream>
#include <fstream>
#include <sndfile.hh>
#include <vector>
#include <cmath>
#include <math.h>
#include "wav_hist.h"

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536;

int main(int argc, char **argv){
    SndfileHandle input{argv[1]};
    SndfileHandle output{argv[2], SFM_WRITE, input.format(), input.channels(), input.samplerate()};
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <input_wav> <output_wav> <effect> <wanted_effect> [delay | freq] [gain]\n" << endl;
        return 1;
    }
    if (input.error()){
        cerr << "Error opening input file " << argv[1] << endl;
        return 1;
    }
    if (output.error()){
        cerr << "Error opening output file " << argv[3] << endl;
        return 1;
    }
    if ((input.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV){
        cerr << "Input file " << argv[2] << " is not a WAV file" << endl;
        return 1;
    }
    if ((input.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16){
        cerr << "Input file " << argv[2] << " is not a 16-bit PCM WAV file" << endl;
        return 1;
    }
    string effect = argv[3];
    if (effect != "SingleEcho" && effect != "MultipleEcho" && effect != "AmplitudeModulation" && effect != "reverse"){
        cerr << " Must be one of the following: singleEcho, multipleEcho, amplitudeModulation, reverse" << endl;
        return 1;
    }

    /////////////////////////////////////////////////

    float ganho = 0.8;
    int atraso = 44100;
    float frequencia = 1.0;

    vector<short> samples(FRAMES_BUFFER_SIZE * input.channels());
    vector<short> out_smp;
    out_smp.resize(0);
    size_t nFrames;
    short sample_out;

    if(effect == "SingleEcho" || effect == "MultipleEcho")
    {
        while (nFrames = input.readf(samples.data(), FRAMES_BUFFER_SIZE))
        {
            
                samples.resize(nFrames * input.channels() );

                for (int i = 0; i < (int)samples.size(); i++)
                {
                    if(i >= atraso){
                        sample_out = (samples.at(i) + ganho * samples.at(i - atraso))/ (1 + ganho);

                    }
                    else if (effect == "MultipleEcho"){
                        sample_out = (samples.at(i) + ganho * out_smp.at(i - atraso))/ (1 + ganho);
                    }
                    else{
                        sample_out = samples.at(i);
                    }
                out_smp.insert(out_smp.end(), sample_out);
                    
                }
            
        }
    }
    else if (effect == "AmplitudeModulation")
    {

        while (nFrames = input.readf(samples.data(), FRAMES_BUFFER_SIZE))
        {
            
                samples.resize(nFrames * input.channels() );

                for (int i = 0; i < (int)samples.size(); i++)
                {
                    sample_out = samples.at(i) * cos(2 * M_PI * i * (frequencia/ input.samplerate()));
                    out_smp.insert(out_smp.end(), sample_out);
                }
            
        }
    }

   output.writef(out_smp.data(), out_smp.size() / input.channels());

}
    


    

