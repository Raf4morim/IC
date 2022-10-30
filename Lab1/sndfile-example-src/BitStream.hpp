#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <bitset>

using namespace std;

class BitStream {
    private:
        struct BitBuffer{
            unsigned char byte = 0;
            int contagem = 0;
        };
        BitBuffer bitBuffer;
        fstream ficheiro;
        char modo;

        int ficheiroSize;
        vector<vector<int>> byteV;
        vector<int> bitV;
        int currentArrayPos = 0;

    public:
        BitStream(string filename, char mode) {
            modo = mode;
            if (mode == 'r'){
                ficheiro.open(filename, ios::in | ios::binary);
                ficheiroSize = tamanhoF();
            } else if (mode == 'w') {
                ficheiro.open(filename, ios::out | ios::binary);
            } else {
                throw "Invalid mode";
            }
        }
        int tamanhoF() {
            ficheiro.seekg(0, ios::end);
            int size = ficheiro.tellg();
            ficheiro.seekg(0, ios::beg);
            return size;
        }
        vector<int> revbitV(){
            vector<int> bitV;
            for (int i = 0; i < 8; i++){
                bitV.push_back((bitBuffer.byte >> i) & 1); // le um bit do byte e coloca no array
            }
            vector<int> reversedbitV;
            for (int i = 7; i >= 0; i--){
                reversedbitV.push_back(bitV[i]);
            }
            return reversedbitV;
        }
 
        int readBit() {
            if (modo != 'r') throw "Invalid mode";
            if (bitBuffer.contagem == 0) {
                ficheiro.read((char*)&bitBuffer.byte, 1);
                bitV = revbitV();
            }
            int bit = bitV[bitBuffer.contagem];
            bitBuffer.byte <<= 1;
            bitBuffer.contagem -= 1;
            return bit;
        }

        vector<int> readBits(int n) {
            if (modo != 'r') throw "Invalid mode";
            vector <int> outBits;
            for(int i = 0; i < n; i++){
                if (bitBuffer.contagem == 0) {                      // Leitura chegou ao fim logo temos de ler um novo byte
                    ficheiro.read((char*)&bitBuffer.byte, 1);
                    bitV = revbitV();
                }
                outBits.push_back(bitV[bitBuffer.contagem]);
                bitBuffer.contagem++;
                if (bitBuffer.contagem == 8) {
                    bitBuffer.contagem = 0;
                }
            }
            return outBits;
        }

        void writeBit(int bit) {
            if (modo != 'w') throw "Invalid mode";
            if (bitBuffer.contagem == 8){
                vector<int> invbitV;
                bitBuffer.byte = 0;
                for (int i = 0; i < 8; i++){
                    invbitV.push_back(bitV[7-i]);
                    bitBuffer.byte |= invbitV[i] << i;
                }
                char byte = bitBuffer.byte;
                ficheiro.write(&byte, 1);
                bitBuffer.contagem = 0;
            }
            if (bitBuffer.contagem == 0){
                bitV = std::vector<int>(8);
            }
            bitV[bitBuffer.contagem] = bit;
            bitBuffer.contagem++;
        }

        void writeBits(std::vector<int> bits) {
            if (modo != 'w') throw "Invalid mode";
            
            int c = 0;
            for(int sz = bits.size(); sz > 0; sz--){
                if (bitBuffer.contagem == 8){
                    vector<int> invbitV;
                    bitBuffer.byte = 0;
                    for (int i = 0; i < 8; i++){
                        invbitV.push_back(bitV[7-i]);
                        bitBuffer.byte |= invbitV[i] << i;
                    }
                    char byte = bitBuffer.byte;
                    ficheiro.write(&byte, 1);
                    bitBuffer.contagem = 0;
                }
                if (bitBuffer.contagem == 0){
                    bitV = std::vector<int>(8);
                }
                bitV[bitBuffer.contagem] = bits[c];
                bitBuffer.contagem++;
                c++;
            }
        }
        void close(){
            vector<int> invbitV;
            if (modo == 'w'){
                for (long unsigned int i = 0; i <= byteV.size(); i++){
                    bitBuffer.byte = 0;
                    for (int i = 0; i < 8; i++){
                        invbitV.push_back(bitV[7-i]);
                        bitBuffer.byte |= invbitV[i] << i;
                    }
                    ficheiro.write((char*)&bitBuffer.byte, 1);
                }
            }
            ficheiro.close();
        }
};