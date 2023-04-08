#include <vector>    
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include "saveEditior.hpp"

using namespace std;

// Endian Swap
void swapByteOrder(unsigned short & us)
{
    us = (us >> 8) |
         (us << 8);
}

void chargementID(vector<string> & itemID)
{
    //L'endroit dans le vector == id
	//La string à cet endroit == le nom de l'objet avec cet id
    ifstream fich_nom_item;
	fich_nom_item.open("./item ids");
	if (! fich_nom_item.is_open())
	{
        cerr << "Erreur, le fichier contenant les nom des items n'a pas pu être chargé." << endl;
		exit(1);
	}
	string val,nom = "rien";
    itemID.push_back("NULL");
    while ( fich_nom_item.good() )
    {
        if ( ! getline(fich_nom_item,val,' ').good() )
            break;

        if ( ! getline(fich_nom_item,nom,'\n').good() )
            break;
		itemID.push_back(nom);
	}
}

void chargementCoffre(vector<unsigned short> & la_merde_avant_le_coffre, map<unsigned short, unsigned short> & coffre, vector<unsigned short> & la_merde_apres_le_coffre)
{
    ifstream fich_save;
	fich_save.open("./user1",ios::in | ios::binary);
	if (! fich_save.is_open())
	{
		cerr << "Erreur, le fichier de sauvegarde n'a pas pu être ouvert" << endl;
		exit(2);
	}
	// 432 correspond to the offset (1B0) of the beginning of the chest
    // I divde by 2 beacause 1 hexa = 1 unsigned short (2 octets), and an unsigned short = int (4 octets)/2 (in size)
    // (and we use unsigned short because they take less space, and we only need 2 bytes space)
    unsigned short taille_avant_coffre =  432/2;
    for (int rep = 0; rep <= taille_avant_coffre; ++rep)
    {
        unsigned short id_act;
        fich_save.read((char *)&id_act, sizeof(unsigned short));
        la_merde_avant_le_coffre.push_back(id_act);
    }
    // allez voir seek : https://en.cppreference.com/w/cpp/io/basic_istream/seekg
	// 4432 correspond to the offset of the beginning of the equipement chest (and so, the end off the item one)
	// So, size of the chest= offset of the equipement chest - item chest
	// And there we divide by 4 bc 
    unsigned short taille_coffre = 4432/4 - taille_avant_coffre ;
    fich_save.seekg(taille_avant_coffre);
	for (int rep = 0; rep < taille_coffre; rep++)
	{
        unsigned short id_item_act,  nb_item_act;

		// should byte swap again when saving
        fich_save.read((char *)&id_item_act, sizeof(unsigned short));
		swapByteOrder(id_item_act);
        fich_save.read((char *)&nb_item_act, sizeof(unsigned short));
        swapByteOrder(nb_item_act);
		// Check if the item is already in the map
		// And if so, we add the just found quantity to the already existing one.
        if (auto trouve = coffre.find(id_item_act); trouve == coffre.end() )
            coffre[id_item_act] = nb_item_act;
        else
            trouve->second += nb_item_act;
	}
    while (! fich_save.eof())
    {
        unsigned short id_act;
        fich_save.read((char *)&id_act, sizeof(unsigned short));
        la_merde_apres_le_coffre.push_back(id_act);
    }
}
