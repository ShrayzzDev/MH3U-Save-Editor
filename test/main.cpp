#include "coffre.hpp"
#include "item.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

int main (void)
{
	Item item1{0x3,5};
	list<Item> coffre;
	vector<string> itemID;
	ifstream fich_nom_item("./item ids");
	if (!fich_nom_item)
	{
		cout << "Erreur, le fichier contenant les nom des items n'as pas pu être chargé.";
		return -1;
	}
	string ligne, nom_item = "";
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
	cout << item1.getName(itemID) << endl;
	return 0;
}