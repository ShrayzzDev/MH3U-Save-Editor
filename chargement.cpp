#include <vector>    
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include "saveEditior.hpp"

using namespace std;

//Permet de Endian Swap
void swapByteOrder(short & us)
{
    us = (us >> 8) |
         (us << 8);
}

void chargementID(vector<string> & itemID)
{
    //L'endroit dans le vector == id
	//La string à cet endroit == le nom de l'objet avec cet id
	fstream fich_nom_item;
	fich_nom_item.open("./item ids");
	if (! fich_nom_item.is_open())
	{
		cout << "Erreur, le fichier contenant les nom des items n'a pas pu être chargé." << endl;
		exit(1);
	}
	string val,nom = "rien";
	while (nom != "Slimecoat Jwl 1")
	{
		getline(fich_nom_item,val,' ');
		getline(fich_nom_item,nom,'\n');
		itemID.push_back(nom);
	}
	fich_nom_item.close();
}

fstream fich_save;
void chargementCoffre(vector<int> & la_merde_avant_le_coffre, map<unsigned int, unsigned int> & coffre)
{
	fich_save.open("./user1",ios::in | ios::binary);
	if (! fich_save.is_open())
	{
		cout << "Erreur, le fichier de sauvegarde n'a pas pu être ouvert" << endl;
		exit(2);
	}
	//432 correspond à l'offset (1B0) du début du coffre
	//On divise par deux car 1 hexa = 1 short, et un short = 2 int (en taille)
	//(et on utilise des short car utilisent moins de mémoire, et on manipule par 2 octets et un int en fait 4)
	unsigned short taille_avant_coffre =  432/2;
	//Pleins de chiffres hexadécimaux qui me servent pas tant que je fait que le coffre
	//Viendra à changer si je fait autre chose.
	short temp = 0, id_item_act, nb_item_act;
	for (unsigned short rep = 0; rep < taille_avant_coffre; rep++)
	{
		fich_save.read((char *)&temp, sizeof(short));
		la_merde_avant_le_coffre.push_back(temp);
	}
	//4432 correspond à l'offset du début du coffre à équipement (donc la fin de celui à item)
	//Donc la taille du coffre = offset du coffre à équipement - celui du coffre à item
	//Et on divise toujours par 2 pour les mêmes raisons
	unsigned short taille_coffre = 4432/2 - 432/2 ;
	cout << taille_coffre << endl;
	for (unsigned short rep = 0; rep < taille_coffre; rep++)
	{
		//faudra probablement penser à les re byte-swap à la fin
		fich_save.read((char *)&id_item_act, sizeof(short));
		swapByteOrder(id_item_act);
		fich_save.read((char *)&nb_item_act, sizeof(short));
		swapByteOrder(nb_item_act);
		//Vérifie si l'objet n'existe pas déjà dans la map
		//Et si c'est le cas, on rajoute le nombre qu'on vient de trouver à celui déjà existant.
		if (auto trouve = coffre.find(id_item_act - 1); trouve != coffre.end())
			trouve->second = trouve->second + nb_item_act;
		else
			coffre[id_item_act - 1] = nb_item_act;
	}
	fich_save.close();
}