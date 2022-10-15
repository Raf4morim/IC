#include "BitStream.hpp"

#include <math.h>
#include <string>

using namespace std;


BitStream::BitStream() {
    mode = 0;
    size = 0;
    pos = 0;
    buffer = 0;
}

BitStream::BitStream(const char *filename, char modein) {
    mode = modein;
    size = 0;
    pos = 0;
    buffer = 0;

    if (mode == 'r') {
        file.open(filename, ios::in | ios::binary);
    } else if (mode == 'w') {
        file.open(filename, ios::out | ios::binary);
    }

    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }

    if (mode == 'r') {
        file.seekg(0, ios::end);
        size = file.tellg();
        file.seekg(0, ios::beg);
    }

}


unsigned char BitStream::readBit() {
    if (mode != 'r') {
        cerr << "Error: file not open for reading" << endl;
        exit(1);
    }

    if (pos == 0) {
        file.read((char *) &buffer, 1);
        pos = 8;
    }

    unsigned char bit = buffer & 1;
    buffer >>= 1;
    pos--;

    return bit;
}

void BitStream::writeBit(unsigned char bit) {
    if (mode != 'w') {
        cerr << "Error: file not open for writing" << endl;
        exit(1);
    }

    buffer |= bit << pos;
    pos++;

    if (pos == 8) {
        file.write((char *) &buffer, 1);
        pos = 0;
        buffer = 0;
    }
}

void BitStream::readNBits(unsigned char *bits, int n) {
    for (int i = 0; i < n; i++) {
        bits[i] = readBit();
    }
}

void BitStream::writeNBits(unsigned char *bits, int n) {
    for (int i = 0; i < n; i++) {
        writeBit(bits[i]);
    }
}

bool BitStream::eof() {
    if (mode != 'r') {
        cerr << "Error: file not open for reading" << endl;
        exit(1);
    }

    if (pos == 0) {
        return file.eof();
    } else {
        return false;
    }
}

void BitStream::close() {
    if (mode == 'w') {
        if (pos != 0) {
            file.write((char *) &buffer, 1);
        }
    }

    file.close();
}