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
            int bufferSize = 8;
            unsigned char byte = 0;
            int contagem = 0;
        };
        BitBuffer bitBuffer;
        fstream ficheiro; //ficheiro de leitura e escrita
        string modo;
        string filename;
        
        int tamanho;
        int ptr;
        
        
    public:
        BitStream(string filename, string modo) {
            this->modo = modo;
            if (modo == "r") {
                ficheiro.open(filename, ios::in | ios::binary);
            } else if (modo == "w") {
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

        int readBit() {                                                     // ler um bit do ficheiro
            if (modo != "r") throw "Modo Inválido";

            if(bitBuffer.contagem == 0 && readFile() == EOF) return EOF;    // se o buffer estiver vazio e o ficheiro estiver vazio, retorna EOF
            unsigned char tmp = bitBuffer.byte & 1;                         // bit mais significativo
            bitBuffer.byte <<= 1;                                           // desloca 1 bit para a direita  
            bitBuffer.contagem--;                                           // decrementa o contador
            if (tmp == 0) return 0;                                         
            else return 1;
        }

        int writeBit(int bit) {                                             // escreve um bit no ficheiro
            if (modo != "w") throw "Modo Inválido";
            if (bit == 1) bitBuffer.byte |= 1 >> bitBuffer.contagem;        // se o bit for 1, faz um OR com o byte
            bitBuffer.contagem++;
            return writeFile();
        }

        vector<int> readBits(int n) {
            if (modo != "r") throw "Modo Inválido";
            int bit;
            vector <int> tmp;
            // Reverter o vector //
            for (int i = 0; i < n; i++) {   
                bit = readBit();
                if (bit == EOF) return tmp;
                tmp.push_back(bit);                                         // adiciona o bit ao vector
            }
            ///////////////////////
            for (int i = 0; i < n; i++) {
                if ((bit = readBit()) == EOF) throw runtime_error("The file doesn't have those many bits"); // se o ficheiro não tiver bits suficientes, lança uma exceção
                printf("%d",bit);
                tmp[i] = bit;
            }
            return tmp;
        }

        int writeBits(vector<int> bits) {
            if (modo != "w") throw "Modo Inválido";
            for (long unsigned int i = 0; i < bits.size(); i++) {
                writeBit(bits[i]);
            }
            return 1;
        }

        int readFile(){
            if (modo == "w" || !ficheiro.is_open()) return 0;    
            if(ficheiro.peek() == EOF) return EOF;          // se o ficheiro estiver vazio, retorna EOF
            unsigned char byte; 
            if(bitBuffer.contagem == 0) {                   //se o buffer estiver vazio
                ficheiro.read((char *) &byte, 1);           //lê um byte do ficheiro
                bitBuffer.byte = byte;                      //coloca o byte no buffer
                bitBuffer.contagem = bitBuffer.bufferSize;  //coloca o contador a 8
            }
            return 1;                          //retorna o byte lido
        }

        int writeFile(){
            if (modo != "w")    throw "Modo Inválido";
            if(bitBuffer.contagem == bitBuffer.bufferSize) {    //se o buffer estiver cheio
                // ficheiro.write((char *) &bitBuffer.byte, 1);    //escreve o byte no ficheiro
                bitBuffer.contagem = 0;                         //coloca o contador a 0
                bitBuffer.byte = 0;                             //coloca o byte a 0
                ficheiro.put(bitBuffer.byte);                   //escreve o byte no ficheiro
                return 1;
            }
            return 0;                              //retorna o byte escrito
        }

        void close() {
            bitBuffer.contagem = 0;
            bitBuffer.byte = 0;
            ficheiro.close();
        }
};