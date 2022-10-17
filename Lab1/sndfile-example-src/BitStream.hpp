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
        int pointer;
        unsigned char buffer;

    
    public:
            BitStream();
            BitStream(const char *filename, char mode);
            unsigned char readBit();
            void writeBit(char bit);
            void readNBits(int n, unsigned char *bits);
            void writeNBits(int n, unsigned char *bits);
            bool eof();
            void close();
};


#endif