#include <iostream>
#include "BitStream.hpp"

using namespace std;

int main (int argc, char *argv[]) {	
    ifstream iFile (argv [1], ios::in) ;                                    
    string oFile = argv[2];

    if (argc != 3) {	
        cerr << "Usage: " << argv [0] << " <input file> <output file>\n" ;
        return 1 ;
    } 

    if (! iFile) {
        cerr << "Error: could not open input file.\n" ;
        return 1 ;
    }

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