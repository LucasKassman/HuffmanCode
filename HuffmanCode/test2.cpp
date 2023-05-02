#include "uncompress.hpp"
#include <iostream>

int main(int x, char** args){
    FancyInputStream* read = new FancyInputStream(args[1]);
    FancyOutputStream* write = new FancyOutputStream(args[2]);
    if (read->filesize()==0) {
        delete read;
        delete write;
        return 0;
    }
    readFile(*read, *write);
    write->flush();
    delete read;
    delete write;
    return 0;
}
