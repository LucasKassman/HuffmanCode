#include <stack>
#include "HCTree.hpp"
#include <iostream>
#include <list>
using namespace std;
bool done;
list<HCNode*> delList;
        /**
         * Use the Huffman algorithm to build a Huffman coding tree.
         * PRECONDITION: freqs is a vector of ints, such that freqs[i] is the frequency of occurrence of byte i in the input file.
         * POSTCONDITION: root points to the root of the trie, and leaves[i] points to the leaf node containing byte i.
         */
        void HCTree::build(const vector<unsigned int>& freqs){
           priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> qu;
            done = false;


            for (int i=0; i<256; i++){
                leaves[i] = new HCNode(freqs[i],i+0,1);
                leaves[i]->c0 = nullptr;
                leaves[i]->c1 = nullptr;
                qu.push(leaves[i]);
            }

            
        bool go = true;
        HCNode* temp;
        while (go){
        

            temp = new HCNode(0, '#', 0);
            delList.push_back(temp);
            temp->c0 = qu.top();
            temp->c0->p = temp;
            qu.pop();

            temp->c1 = qu.top();
            qu.pop();
            temp->c1->p=temp;
            temp->count = temp->c1->count + temp->c0->count;
            if (qu.empty()) go=false;
            qu.push(temp);
            
        }
        root = temp;

        }


        void deleteNode(HCNode* delNode){

            if (delNode == NULL) return;
            if (delNode == nullptr) return;
            if (delNode->c0 != nullptr) deleteNode(delNode->c0);
            if (delNode->c1 != nullptr) deleteNode(delNode->c1);
            delete delNode;
            delNode = nullptr;
        }

        HCTree::~HCTree(){
           //  deleteNode(root);
           for (HCNode* i : leaves){
               delete i;
           }
           for (HCNode* i : delList){
               delete i;
           }
           
        }
        

        

        /**
         * Write to the given FancyOutputStream the sequence of bits coding the given symbol.
         * PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
         */
        void HCTree::encode(unsigned char symb, FancyOutputStream & out) const{
            stack<int> revStack;
            HCNode* temp;
            bool go = true;
            for (HCNode* i : leaves){
                if (i->symbol==symb){
                    while(go){

                        if(i!=root){
                        temp = i->p;
                        if(temp->c0 == i) revStack.push(0); 
                        if(temp->c1 == i) revStack.push(1);
                        i = temp;
                        }
                        else go = false;
                    }
                    break;
                } 

            }
            while (!revStack.empty()){
                out.write_bit(revStack.top());
                revStack.pop();
            }
           // out.flush_bitwise();
        }

        /**
         * Return symbol coded in the next sequence of bits from the stream.
         * PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
         */
        unsigned char HCTree::decode(FancyInputStream & in) const{
            
            HCNode* temp = root;
            bool go = true;
            bool next;
            int check;
            int counter = 0;
            while(go){
                check = in.read_bit();
                if (check == -1){
                    done = true;
                    break;
                }
                next = check;
                if (next == 0){
                    temp = temp->c0;
                }
                if (next ==1){
                    temp = temp->c1;
                }
                if (temp->leaf){
                    return temp->symbol;
                }
                counter++;
                if(counter >= 8) go =false;
            }
            return 0;
            
        }
bool HCTree::donezo(){
    return done;
}



