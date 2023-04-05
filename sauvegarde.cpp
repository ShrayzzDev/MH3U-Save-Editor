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
    map<unsigned short, unsigned short>::iterator it;
    for (it = coffre.begin(); it != coffre.end(); ++it)
    {
        unsigned short temp = it->first;
        swapByteOrder(temp);
        nv_save.write((char*)&temp,2);
        swapByteOrder(it->second);
        nv_save.write((char*)&temp,2);
    }
    for (unsigned short oct : la_merde_apres_le_coffre)
    {
        swapByteOrder(oct);
        nv_save.write((char*)&oct,2);
    }
}