#ifndef WAVQUANT_H
#define WAVQUANT_H

#include <iostream>
#include <sndfile.hh>
#include <vector>
#include <cmath>

class WAVQuant
{
private:
    std::vector<short> counts;

public:
    WAVQuant(const size_t n_samples, size_t n_bits)
    {
        counts.resize(n_samples);
    }

    void update(const std::vector<short> &samples, size_t n_bits)
    {
        size_t n{};
        for (auto s : samples)
            counts[n++] = s;

        for (n = 0; n < samples.size(); n++)
        {
            counts[n] = counts[n] >> (16 - n_bits);
            counts[n] = counts[n] << (16 - n_bits);
        }
    }
    void toFile(SndfileHandle output) const
    {
        output.write(counts.data(), counts.size());
    }
};

#endif
