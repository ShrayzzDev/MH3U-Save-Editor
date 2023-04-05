#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <string>

#include "saveEditior.hpp"

using namespace std;

ostream & operator<<(ostream & os, map<unsigned short, unsigned short> & coffre)
{
	for (pair<unsigned short, unsigned short> item : coffre)
		os << "Vous avez " <<  item.second << " item(s) d'id " << item.first << endl;
	return os;
}

ostream & operator<<(ostream & os, vector<string> & itemID)
{
	for (int i = 0; i < itemID.size(); i++)
		os << "Id de l'item: " << i << endl << "Nom Correspondant " << itemID.at(i) << endl;
	return os;
}

int main (void)
{
	//Item item1{0x3,5};
	//istringstream temp_pour_convertir;
	vector<string> itemID;
	chargementID(itemID);
	//cout << itemID << endl;
	vector<unsigned short> la_merde_avant_le_coffre, la_merde_apres_le_coffre;
	//La clé c'est l'id en hexa
	//La valeur c'est le nombre d'item dans le coffre
	//C'est possible sachant que un item peux pas être présent plusieurs fois dans le coffre
	//C'est pas comme un coffre Minecraft
	map<unsigned short, unsigned short> coffre;
	chargementCoffre(la_merde_avant_le_coffre,coffre,la_merde_apres_le_coffre);
	//string testNomItem = "Organizer Guide";
	//ajouterItem(coffre,8);
	//ajouterItem(coffre,4522);
	//ajouterItem(coffre,testNomItem,itemID);
	//changerQte(coffre);
    map<unsigned short, unsigned short>::iterator debut = coffre.begin(), fin = coffre.end(), it;
    for (it = debut; it != fin; ++it)
	{
		if (it->first == 0)
			cout << "Cet emplacement est vide" << endl;
        else {
            if (it->first < itemID.size() ) {
                cout << "Vous avez " << hex << it->second << " " << "(id: " << hex << it->first << ") " << itemID.at(it->first) << " dans votre coffre." << endl;
            } else {
                cerr << "Unknown item id : " << it->first << endl;
            }
        }
	}
    sauvegarde(la_merde_avant_le_coffre,coffre,la_merde_apres_le_coffre);
	//cout << coffre << endl;
	return 0;
}














//istringstream temp(val);
//unsigned int hex_temp		
//temp >> hex >> hex_temp;

	/* ligne, nom_item = "";
	char test;
	int id;
	fich_nom_item >> id;
	fich_nom_item.get(test);
	while (test != '\n')
	{
		nom_item = nom_item + test;
		fich_nom_item.get(test);
	}
	itemID.push_back(nom_item);
	while (getline(fich_nom_item,ligne))
	{
		string nom_item = "";
		fich_nom_item >> id;
		fich_nom_item.get(test);
		while (test != '\n')
		{
			nom_item = nom_item + test;
			fich_nom_item.get(test);
		}
		itemID.push_back(nom_item);
	}
	cout << item1.getName(itemID) << endl;*/
