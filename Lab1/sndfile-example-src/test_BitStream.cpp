#include "BitStream.hpp"

int main(int argc,char** argv){
    BitStream bs("test.txt",'w');
    unsigned char bits[8] = {1,0,1,0,1,0,1,0};
    bs.writeNBits(8,bits);
    bs.close();
    return 0;

}
