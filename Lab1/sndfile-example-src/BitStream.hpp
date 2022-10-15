#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h>

using namespace std;

class BitStream {
    private:
        fstream file;
        int mode;
        int size;
        int pos;
        int buffer;

    
    public:

    BitStream();

    BitStream(const char *filename, char modein);

    unsigned char readBit();

    void writeBit(unsigned char bit);

    void readNBits(unsigned char *bits, int n);

    void writeNBits(unsigned char *bits, int n);

    bool eof();

    void close();

};


#endif