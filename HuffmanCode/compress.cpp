#include "compress.hpp"
#include <iostream>
#include <stack>
#include <stdio.h>
#include <string.h>
vector<unsigned int> freqs(256);
HCTree* tree;

void countFreq(FancyInputStream & in){
    in.reset();
    for (int i: freqs){
        freqs[i]=0;
    }
    
    unsigned int cha;
    bool go = true;
    int get;
    while (go){
        get = in.read_byte();

        if (get==-1) break;
        cha = get + 0;
        freqs[cha]++;
    }

    in.reset();

}

void writeHeader(FancyOutputStream & out){
   unsigned char chop[4];
    for (int i:freqs){
        memcpy(chop, &i, sizeof(int));
        //out.write_int(i);
       /* if (i>0){
            cout << 0 + chop[0] << endl;
            cout << 0 + chop[1] << endl;
            cout << 0 +chop[2] << endl;
            cout << 0 + chop[3] << endl;

        }*/
        out.write_byte(chop[0]);
        out.write_byte(chop[1]);
        out.write_byte(chop[2]);
    }


}
void writeFile(FancyOutputStream & out, FancyInputStream & in){
    stack<bool> revStack;
    bool go = true;
    int ch;
    while (go){
        ch = in.read_byte();
        if (ch==-1) break;
        tree->encode(ch+0, out);
    }
}


void gogo(FancyInputStream* re, FancyOutputStream* wr){

    countFreq(*re);
    tree = new HCTree();
    tree->build(freqs);
    writeHeader(*wr);
    writeFile(*wr,*re);
    tree->~HCTree();
   // delete tree;




}



