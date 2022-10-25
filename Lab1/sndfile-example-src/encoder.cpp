#include <iostream>
#include "BitStream.hpp"

using namespace std;

int main (int argc, char *argv[]) {	

    //this program converts a ".txt" file that contains only 1's and 0's into a binary file using the bit_stream class

    if (argc != 3) {	
        cerr << "Usage: " << argv [0] << " <input file> <output file>\n" ;
        return 1 ;
    } 

    ifstream iFile (argv [1], ios::in) ;
    if (! iFile) {
        cerr << "Error: could not open input file.\n" ;
        return 1 ;
    }

    string oFile = argv[2];

    string line;
    getline(iFile, line);
    cout << "Input file: " << line << endl;
    cout << "Input file length: " << line.length() << endl;
    iFile.close();

    BitStream outputFile (oFile, "w") ;

    vector<int> bits;
    for (long unsigned int i = 0; i < line.length(); i++){
        bits.push_back(line[i] - '0');
    }
    outputFile.writeBits(bits);
    outputFile.close();

    return 0;
} ; 