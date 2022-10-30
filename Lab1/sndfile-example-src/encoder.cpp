#include <iostream>
#include "BitStream.hpp"

using namespace std;

int main (int argc, char *argv[]) {	
    ifstream iFile (argv [1], ios::in) ;                                 
    string oFile = argv[2];

    if (argc != 3) throw "Usage: ../sndfile-example-bin/encoder <input file> <output file>" ;
    if (! iFile) throw "Error: could not open input file." ;

    string line;
    getline(iFile, line);                                       
    cout << "\n" << line << endl;                     
    iFile.close();

    BitStream outputFile (oFile, 'w') ;

    vector<int> bits;
    for (long unsigned int i = 0; i < line.length(); i++){
        bits.push_back(line[i] - '0');
    }
    outputFile.writeBits(bits);
    outputFile.close();

    return 0;
} ; 