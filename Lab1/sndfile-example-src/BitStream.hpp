#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <sstream>
#include <bitset>
#include <algorithm>

using namespace std;

class BitStream {
    private:
        struct BitBuffer{
            unsigned const int bufferSize = 8;
            unsigned char byte = 0;
            int contagem = 0;
        };
        BitBuffer bitBuffer;
        fstream ficheiro; //ficheiro de leitura e escrita
        string modo;
        string filename;
        // //create a variable that hold multiple arrays of 8 bits
        // std::vector<std::vector<int>> byteArray;
        // //create a variable that holds the current array of 8 bits
        // std::vector<int> bitArray;
        int tamanho;
        int ptr;
        
    public:
        BitStream(string filename, string modo) {
            this->modo = modo;
            if (modo == "r") {
                ficheiro.open(filename, ios::in | ios::binary);
            } else if (modo == "w") {
                ptr = 8;
                ficheiro.open(filename, ios::out | ios::binary);
            } else {
                throw "Modo inválido";
            }

            if(!ficheiro.is_open())
                throw runtime_error("Não consegue abrir o ficheiro!");
        }
        int tamanhoF() {
            ficheiro.seekg(0, std::ios::end);
            int size = ficheiro.tellg();
            ficheiro.seekg(0, std::ios::beg);
            return size;
        }
        
        unsigned char readBit() {
            if (modo != "r") throw "Modo Inválido";
            if(bitBuffer.contagem == 0 && readFile() == EOF) return EOF;
            unsigned char tmp = bitBuffer.byte & 1;                         //bit mais significativo
            bitBuffer.byte >>= 1;                                           //desloca 1 bit para a direita  
            bitBuffer.contagem--;                                           //decrementa o contador
            if (tmp == 0) return 0;
            else return 1;
        }

        int writeBit(char bit) {
            if (modo != "w") throw "Modo Inválido";
            if (bit == 1) bitBuffer.byte |= 1 << bitBuffer.contagem;  //bit mais significativo a 1 
            bitBuffer.contagem++;
            return writeFile();
        }

        vector<int> readBits(int n) {
            if (modo != "r") throw "Modo Inválido";
            int bit;
            vector <int> tmp;
            
            for (int i = 0; i < n; i++) {
                if ((bit = readBit()) == EOF) throw std::runtime_error("The file doesn't have those many bits");
                printf("%d",bit);
                tmp[i] = bit;
            }
            return tmp;
        }

        int writeBits(vector<int> bits) {
            if (modo != "w") throw "Modo Inválido";
            for (int i = 0; i < bits.size(); i++) {
                writeBit(bits[i]);
            }
            return 1;
        }

        int readFile(){
            if (modo != "r")    throw "Modo Inválido";      
            if(ficheiro.peek() == EOF) return EOF;
            if(bitBuffer.contagem == 0) {                   //se o buffer estiver vazio
                ficheiro.read((char *) &bitBuffer.byte, 1); //lê um byte do ficheiro
                bitBuffer.contagem = bitBuffer.bufferSize;  //coloca o contador a 8
            }
            return bitBuffer.byte;                          //retorna o byte lido
        }

        int writeFile(){
            if (modo != "w")    throw "Modo Inválido";
            if(bitBuffer.contagem == bitBuffer.bufferSize) {    //se o buffer estiver cheio
                ficheiro.write((char *) &bitBuffer.byte, 1);    //escreve o byte no ficheiro
                bitBuffer.contagem = 0;                         //coloca o contador a 0
                bitBuffer.byte = 0;                             //coloca o byte a 0
                ficheiro.put(bitBuffer.byte);                   //escreve o byte no ficheiro
            }
            return bitBuffer.byte;                              //retorna o byte escrito
        }

        void close() {
            bitBuffer.contagem = 0;
            bitBuffer.byte = 0;
            ficheiro.close();
        }
};
#endif