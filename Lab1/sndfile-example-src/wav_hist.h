#ifndef WAVHIST_H
#define WAVHIST_H

#include <iostream>
#include <vector>
#include <map>
#include <sndfile.hh>
#include <fstream>

class WAVHist {
  private:
	std::vector<std::map<short, size_t>> counts;
	std::map<short,size_t> mid_channel;
	std::map<short, size_t> side_channel;

  public:
	WAVHist(const SndfileHandle& sfh) {
		counts.resize(sfh.channels());
	}

	void update(const std::vector<short>& samples) {
		size_t n { };
		for(auto s : samples)// reconhece o tipo automaticamente
			counts[n++ % counts.size()][s]++;
	

	for(n = 0; n+1 < samples.size(); n += 2)
	{
		mid_channel[((samples[n] + samples[n+1])/2)]++;
		side_channel[((samples[n] - samples[n+1])/2)]++;

	}

	 	//MID CHANNEL
		std::ofstream out_file("./LAB1/sndfile-example-src/MID_channel.txt");
		for(auto [value, counter] : mid_channel)
			out_file << value << '\t' << counter << '\n';
		out_file.close();

		//SIDE CHANNEL
		std::ofstream out_file2("./LAB1/sndfile-example-src/SIDE_channel.txt");
		for(auto [value, counter] : side_channel)
			out_file2 << value << '\t' << counter << '\n';

	}





	void dump(const size_t channel) const { // O const 
		for(auto [value, counter] : counts[channel])
			std::cout << value << '\t' << counter << '\n';
	}
};

#endif

