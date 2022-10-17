#include "BitStream.hpp"
#include <math.h>
#include <string>

using namespace std;


BitStream::BitStream() {
    this->mode = 0;
    this->size = 0;
    this->pointer = 0;
    this->buffer = 0;
}

BitStream::BitStream(const char *filename, char mode) {
    if (mode == 'r') {
        this->mode = 1;
        this->file.open(filename, ios::in | ios::binary);
        file.seekg(0, ios::end);
        size = file.tellg();
        file.seekg(0, ios::beg);
    } else if (mode == 'w') {
        this->mode = 0;
        this->pointer = 8;
        this->file.open(filename, ios::out | ios::binary);
    } else {
        throw "Invalid mode";
    }

    buffer = 0;
    if(!file.is_open())
        throw runtime_error("Could not open file");


}

unsigned char BitStream::readBit() {
    if (mode != 1) {
        throw "Invalid mode";
    }

    if (pointer == 8) {
        file.read((char *) &buffer, 1);
        pointer = 0;
    }

    unsigned char bit = (buffer >> (7 - pointer)) & 1;
    pointer++;
    return bit;
}


void BitStream::writeBit(char bit) {
    if (mode != 0) {
        throw "Invalid mode";
    }

    if (pointer == 8) {
        file.write((char *) &buffer, 1);
        pointer = 0;
        buffer = 0;
    }

    buffer |= (bit << (7 - pointer));
    pointer++;
}

void BitStream::readNBits(int n, unsigned char *bits) {
    if (mode != 1) {
        throw "Invalid mode";
    }

    for (int i = 0; i < n; i++) {
        bits[i] = readBit();
    }
}

void BitStream::writeNBits(int n, unsigned char *bits) {
    if (this->mode != 0) {
        throw "Invalid mode";
    }

    for (int i = 0; i < n; i++) {
        this->writeBit(bits[i]);
    }
}

bool BitStream::eof() {
    if (mode != 1) {
        throw "Invalid mode";
    }

    return file.eof();
}

void BitStream::close() {
    if (mode == 0) {
        file.write((char *) &buffer, 1);
    }

    file.close();
}




