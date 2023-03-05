#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <string>
#include <limits>

#include "saveEditior.hpp"

using namespace std;

int main (void)
{
	//Item item1{0x3,5};
	//istringstream temp_pour_convertir;
	vector<string> itemID;
	chargementID(itemID);
	vector<int> la_merde_avant_le_coffre;
	//La clé c'est l'id en hexa
	//La valeur c'est le nombre d'item dans le coffre
	//C'est possible sachant que un item peux pas être présent plusieurs fois dans le coffre
	//C'est pas comme un coffre Minecraft
	map<unsigned int, unsigned int> coffre;
	chargementCoffre(la_merde_avant_le_coffre,coffre);
	map<unsigned int, unsigned int>::iterator début = coffre.begin(), fin = coffre.end(), it;
	for (it = début; it != fin; it++)
			cout << "Vous avez " << it->second << " " << "(id: " << it->first << ") " << itemID[it->first] << " dans votre coffre." << endl;
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
