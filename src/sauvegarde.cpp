#include <vector>    
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include "saveEditor.hpp"

using namespace std;

void sauvegarde(const vector<unsigned short> & avant_le_coffre, const map<unsigned short, unsigned short> & coffre, const vector<unsigned short> & apres_le_coffre)
{
    ofstream nv_save;
    nv_save.open("./new/user1",ios::out | ios::binary );
    for (unsigned short oct : avant_le_coffre)
    {
        nv_save.write((char*)&oct,2);
    }
    // May seem useless, but bc the endian swap function uses reference, so I can't swap if I put it in raw.
    unsigned short max_quant = 99, nb_slot = 0; 
    map<unsigned short, unsigned short>::const_iterator it = coffre.cbegin();
    it++;
    for (it ; it != coffre.end(); ++it)
    {
        unsigned short temp1 = it->first, temp2 = it->second, rep = 0;
        swapByteOrder(temp1);
        // If division by 99 > 1, then there's at least one full slot left.
        while(temp2/99 >= 1)  
        {
            nv_save.write((char*)&temp1,2);
            nv_save.write((char*)&max_quant,2);
            ++rep;
            temp2 = temp2 - 99;
        }
        unsigned short nb_dernier_slot = it->second - rep * 99;
        if (nb_dernier_slot == 0){
            break;
        }
        swapByteOrder(nb_dernier_slot);
        nv_save.write((char*)&temp1,2);
        nv_save.write((char*)&nb_dernier_slot,2);
        nb_slot += rep + 1;
    }
    unsigned short empty_space = (4432/2 - 432)/2 - nb_slot;
    for (int rep = 0; rep < empty_space; ++rep)
    {
        unsigned int zero = 0;
        nv_save.write((char*)&zero,4);
    }
    for (unsigned short oct : apres_le_coffre)
    {
        nv_save.write((char*)&oct,2);
    }
}