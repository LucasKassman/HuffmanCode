#include "uncompress.hpp"


HCTree* tree;
vector<unsigned int> freqss(256);





void readFile(FancyInputStream & read, FancyOutputStream & write){
    unsigned char chop[4];
    chop[3] = 0;
    unsigned int now;
    for (int i=0;i<256;i++){
        chop[0] = read.read_byte();
        chop[1] = read.read_byte();
        chop[2] = read.read_byte();
        now = (unsigned int)(chop[3] << 24 | chop[2] << 16 | chop[1] << 8 | chop[0]);
        freqss[i] = now;

      //  freqss[i] = read.read_int();

    }
    tree = new HCTree();
    tree->build(freqss);

    unsigned char ch; 
    bool go = true;
    while (go){
        ch = tree->decode(read);
        if (tree->donezo()) return; 
        write.write_byte(ch);
    }
    tree->~HCTree();
   // delete tree;





}
