#include <vector>    
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include "saveEditor.hpp"

using namespace std;

void sauvegarde (vector<unsigned short> & la_merde_avant_le_coffre, map<unsigned short, unsigned short> & coffre, vector<unsigned short> & la_merde_apres_le_coffre)
{
    ofstream nv_save;
    nv_save.open("./new/user1",ios::out | ios::binary );
    for (unsigned short oct : la_merde_avant_le_coffre)
    {
        // swapByteOrder(oct);
        cout << oct << endl;
        nv_save.write((char*)&oct,2);
    }
    // May seem useless, but bc the endian swap function uses reference, so I can't swap if I put it in raw.
    unsigned short max_quant = 99, nb_slot = 0; 
    // swapByteOrder(max_quant);
    map<unsigned short, unsigned short>::iterator it = coffre.begin();
    it++;
    cout << " ----------------- Saving the chest ----------------- " << endl;
    for (it ; it != coffre.end(); ++it)
    {
        unsigned short temp1 = it->first, temp2 = it->second, rep = 0;
        swapByteOrder(temp1);
        cout << " -------- item id -------- " << endl;
        cout << temp1 << endl;
        cout << " -------- quantity -------- " << endl;
        cout << "total quantity = " << temp2 << endl;
        cout << " -------------------------- " << endl;
        // If division by 99 > 1, then there's at least one full slot left.
        while(temp2/99 >= 1)  
        {
            cout << "full slot (99)" << endl;
            nv_save.write((char*)&temp1,2);
            nv_save.write((char*)&max_quant,2);
            ++rep;
            temp2 = temp2 - 99;
        }
        unsigned short nb_dernier_slot = it->second - rep * 99;
        if (nb_dernier_slot == 0){
            break;
        }
        cout << nb_dernier_slot << endl;
        swapByteOrder(nb_dernier_slot);
        nv_save.write((char*)&temp1,2);
        nv_save.write((char*)&nb_dernier_slot,2);
        nb_slot += rep + 1;
        cout << " -------- Nb Slots --------" << endl;
        cout << dec << nb_slot << endl;
    }
    unsigned short empty_space = (4432/2 - 432)/2 - nb_slot;
    cout << "Nb slot: " << dec << nb_slot << endl;
    cout << "Nb slot vides: " << dec << empty_space << endl;
    cout << dec << (4432/2 - 432/2)/2 << endl;
    for (int rep = 0; rep < empty_space; ++rep)
    {
        unsigned int zero = 0;
        nv_save.write((char*)&zero,4);
    }
    for (unsigned short oct : la_merde_apres_le_coffre)
    {
        swapByteOrder(oct);
        nv_save.write((char*)&oct,2);
    }
}