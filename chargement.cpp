#include <vector>    
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include "saveEditior.hpp"

using namespace std;

//Permet de Endian Swap
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
    while ( fich_nom_item.good() )
    {
        if ( ! getline(fich_nom_item,val,' ').good() )
            break;

        if ( ! getline(fich_nom_item,nom,'\n').good() )
            break;
		itemID.push_back(nom);
	}
}


// PROBLEME: Pour une raison indeterminée, remaplce parfois le premier octet des items par des ff
// Plus fait apparaître des items en pleins milieu (retrouve pas ce qu'il y en recherchant les valeurs hex dans le fichier)
void chargementCoffre(vector<unsigned short> & la_merde_avant_le_coffre, map<unsigned short, unsigned short> & coffre)
{
    ifstream fich_save;
	fich_save.open("./user1",ios::in | ios::binary);
	if (! fich_save.is_open())
	{
		cout << "Erreur, le fichier de sauvegarde n'a pas pu être ouvert" << endl;
		exit(2);
	}
	//432 correspond à l'offset (1B0) du début du coffre
    //On divise par deux car 1 hexa = 1 unsigned short, et un unsigned short = 2 int (en taille)
    //(et on utilise des unsigned short car utilisent moins de mémoire, et on manipule par 2 octets et un int en fait 4)
	//Et on redivise par 10 car il y a 10 pages dans le coffre.
    unsigned short taille_avant_coffre =  432/2;
	//Pleins de chiffres hexadécimaux qui me servent pas tant que je fait que le coffre
	//Viendra à changer si je fait autre chose.

    for (unsigned short rep = 0; rep < taille_avant_coffre; rep++)
    {
        unsigned short temp;
        fich_save.read((char *)&temp, sizeof(unsigned short));
		la_merde_avant_le_coffre.push_back(temp);
    } // allez voir seek : https://en.cppreference.com/w/cpp/io/basic_istream/seekg
	//4432 correspond à l'offset du début du coffre à équipement (donc la fin de celui à item)
	//Donc la taille du coffre = offset du coffre à équipement - celui du coffre à item
	//Et on divise toujours par 2 pour les mêmes raisons
    unsigned short taille_coffre = 4432/2 - 432/2 ;
	cout << taille_coffre << endl;

	for (int rep = 0; rep < taille_coffre; rep++)
	{
        unsigned short id_item_act,  nb_item_act;

		//faudra probablement penser à les re byte-swap à la fin
        fich_save.read((char *)&id_item_act, sizeof(unsigned short));
		swapByteOrder(id_item_act);
        fich_save.read((char *)&nb_item_act, sizeof(unsigned short));
        swapByteOrder(nb_item_act);
        --id_item_act; // Start at 0 please!
        cout << hex << id_item_act << " " << nb_item_act << endl;
		//Vérifie si l'item n'existe pas déjà dans la map
		//Et si c'est le cas, on rajoute le nombre qu'on vient de trouver à celui déjà existant
        if (auto trouve = coffre.find(id_item_act); trouve == coffre.end() )
            coffre[id_item_act] = nb_item_act;
        else
            trouve->second += nb_item_act;
	}
}
