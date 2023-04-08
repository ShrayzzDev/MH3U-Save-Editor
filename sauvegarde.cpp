#include <vector>    
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include "saveEditior.hpp"

using namespace std;

void sauvegarde (vector<unsigned short> & la_merde_avant_le_coffre, map<unsigned short, unsigned short> & coffre, vector<unsigned short> & la_merde_apres_le_coffre)
{
    ofstream nv_save;
    nv_save.open("./new/user1",ios::out | ios::binary );
    for (unsigned short oct : la_merde_avant_le_coffre)
    {
        swapByteOrder(oct);
        nv_save.write((char*)&oct,2);
    }
    // May seem useless, but bc the endian swap function uses reference, so I can't swap if I put it in raw.
    unsigned short max_quant = 99; 
    swapByteOrder(max_quant);
    map<unsigned short, unsigned short>::iterator it;
    for (it = coffre.begin(); it != coffre.end(); ++it)
    {
        unsigned short temp1 = it->first, rep = 0;
        swapByteOrder(temp1);
        // If division by 99 > 1, then there's at least one full slot left.
        cout << it->second/99 << endl;
        // string test;
        // cin >> test;
        while(it->second/99 > 1)  
        {
            cout << "ça reste bloqué ici" << endl;
            nv_save.write((char*)&temp1,2);
            nv_save.write((char*)&max_quant,2);
            ++rep;
            it->second = it->second - 99;
        }
        unsigned short nb_dernier_slot = it->second - rep * 99;
        swapByteOrder(nb_dernier_slot);
        nv_save.write((char*)&temp1,2);
        nv_save.write((char*)&nb_dernier_slot,2);

    }
    for (unsigned short oct : la_merde_apres_le_coffre)
    {
        swapByteOrder(oct);
        nv_save.write((char*)&oct,2);
    }
}