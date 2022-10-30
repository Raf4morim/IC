#ifndef WAVHIST_H
#define WAVHIST_H

#include <iostream>
#include <vector>
#include <map>
#include <sndfile.hh>
#include <fstream>

class WAVHist
{
private:
	std::map<short, size_t> mid_ch;
	std::map<short, size_t> side_ch;
	std::vector<std::map<short, size_t>> c;

public:
	WAVHist(const SndfileHandle & sfh){
		c.resize(sfh.channels());
	}

	void update(const std::vector<short> & samples)
	{
		for(int i=0; i < (int) samples.size()/2; i+=2){
			c[0][samples[i]]++;
			c[1][samples[i+1]]++;
			mid_ch[(samples[i] + samples[i+1]) / 2]++;
			side_ch[(samples[i] - samples[i+1]) / 2]++;
		}
	}


	void midD(void) {
		std::ofstream midFile("midChannel.dat");
		for (auto [valor, cont] : mid_ch)
			midFile << valor << '\t' << cont << '\n';
		midFile.close();
	}

	void sideD(void) {
		std::ofstream sideFile("sideChannel.dat");
		for (auto [valor, cont] : side_ch)
			sideFile << valor << '\t' << cont << '\n';
		sideFile.close();
	}

	void dump(const size_t channel) const{ // O const
		std::ofstream oF("channel.dat");
		for (auto [valor, cont] : c[channel])
			oF << valor << '\t' << cont << '\n';
		oF.close();
	}
};

#endif
