#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <string>

#include "saveEditor.hpp"

using namespace std;

ostream & operator<<(ostream & os, map<unsigned short, unsigned short> & coffre)
{
	for (pair<unsigned short, unsigned short> item : coffre)
		os << "You have " <<  item.second << " item(s) of id " << item.first << endl;
	return os;
}

void afficheCoffre(map<unsigned short, unsigned short> coffre, vector<string> itemID)
{
	map<unsigned short, unsigned short>::iterator debut = coffre.begin(), fin = coffre.end(), it;
	for (it = debut; it != fin; ++it)
	{
		if (it->first == 0)
			cout << "Cet emplacement est vide" << endl;
        else {
            if (it->first < itemID.size() ) {
                cout << "You have " << dec << it->second << " " << "(id: " << hex << it->first << ") " << itemID.at(it->first) << " in your chest" << endl;
            } else {
                cerr << "Unknown item id : " << it->first << endl;
            }
        }
	}
}

void test (void)
{
	vector<string> itemID;
	chargementID(itemID);
	vector<unsigned short> avant_le_coffre, apres_le_coffre;
	// The key is the id
	// Value is the quantity of the item
	map<unsigned short, unsigned short> coffre;
	chargementCoffre(avant_le_coffre,coffre,apres_le_coffre);
	string testNomItem = "Organizer Guide";
	//ajouterItem(coffre,8);
	//ajouterItem(coffre,4522);
	ajouterItem(coffre,testNomItem,itemID);
	//changerQte(coffre);
    sauvegarde(avant_le_coffre,coffre,apres_le_coffre);
}

int main (void)
{
	int choix = 0;
	vector<string> itemID;
	chargementID(itemID);
	vector<unsigned short> avant_le_coffre, apres_le_coffre;
	// The key is the id
	// Value is the quantity of the item
	map<unsigned short, unsigned short> coffre;
	chargementCoffre(avant_le_coffre,coffre,apres_le_coffre);
	while (0 == 0)
	{
		cout << "----------------------------------------------------" << endl;
		cout << "|                                                  |" << endl;
		cout << "|          Welcome to the MH3U Save Editor         |" << endl;
		cout << "|                                                  |" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "|                                                  |" << endl;
		cout << "|  1. Show Chest                                   |" << endl;
		cout << "|  2. Add an item in the chest with name           |" << endl;
		cout << "|  3. Add an item in the chest with id             |" << endl;
		cout << "|  4. Change the quantity of an item with id       |" << endl;
		cout << "|  5. Change the quantity of an item with name     |" << endl;
		cout << "|                                                  |" << endl;
		cout << "|  98. Quit without saving                         |" << endl;
		cout << "|  99. Quit with saving                            |" << endl;
		cout << "|                                                  |" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << endl;
		cout << "Make a choice :" << endl;
		cin >> choix;
		string name;
		unsigned short id;
		switch (choix)
		{
		case 1:
			afficheCoffre(coffre,itemID); 
			break;

		case 2:
			cout << "Enter the name of the item: " << endl;
			getline(cin >> ws, name);
			ajouterItem(coffre,name,itemID);
			break;

		case 3:
			cout << "Enter the id of the item: " << endl;
			cin >> id;
			ajouterItem(coffre,id);
			break;

		case 4:
    		cout << "Enter the id of the item: " << endl;
    		cin >> id;
			changerQte(coffre,id);
			break;

		case 5:
			cout << "Enter the name of the item: " << endl;
			getline(cin >> ws, name);
			changerQte(coffre,name,itemID);
			break;

		case 98:
			exit(0);
			break;

		case 99:
			sauvegarde(avant_le_coffre,coffre,apres_le_coffre);
			exit(0);
			break;

		default:
			cerr << "Incorrect choice" << endl;
			break;
		}
	}
	return 0;
}