#include "coffre.hpp"
#include "item.hpp"

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

using namespace std;

//Permet de Endian Swap
void swapByteOrder(short & us)
{
    us = (us >> 8) |
         (us << 8);
}
/*
ostream & operator<< (ostream & os, map<unsigned int, unsigned int> & inventaire)
{
	map<unsigned int, unsigned int>::iterator début = inventaire.begin(), fin = inventaire.end(), it;
	for (it = début; it != fin; it++)
		return os << "Vous avez " << it->second << " " << itemID[it->first - 1] << " dans votre coffre." << endl;
	return os;
}*/

int main (void)
{
	//Item item1{0x3,5};
	//L'endroit dans le vector == id
	//La string à cet endroit == le nom de l'objet avec cet id
	vector<string> itemID;
	fstream fich_nom_item;
	fich_nom_item.open("./item ids");
	if (! fich_nom_item.is_open())
	{
		cout << "Erreur, le fichier contenant les nom des items n'a pas pu être chargé." << endl;
		return -1;
	}
	string val,nom = "rien";
	//val = l'id de l'item
	//nom = le nom
	//istringstream temp_pour_convertir;
	while (nom != "Slimecoat Jwl 1")
	{
		getline(fich_nom_item,val,' ');
		//fich_nom_item.ignore(taille_espace,' ');
		getline(fich_nom_item,nom,'\n');
		//On transfrome de manière temporaire le val (qui est à ce moment la un string)
		//En flux de string pour pouvoir le convertir en int dans hex_temp
		//Pour ensuite
		//istringstream temp(val);
		//unsigned int hex_temp;
		//temp >> hex >> hex_temp;
		itemID.push_back(nom);
	}
	fich_nom_item.close();
	fstream fich_save;
	fich_save.open("./user1",ios::in | ios::binary);
	if (! fich_save.is_open())
	{
		cout << "Erreur, le fichier de sauvegarde n'a pas pu être ouvert" << endl;
		return -2;
	}
	//432 correspond à l'offset (1B0) du début du coffre
	//On divise par deux car 1 hexa = 1 short, et un short = 2 int (en taille)
	//(et on utilise des short car utilisent moins de mémoire, et on manipule par 2 octets et un int en fait 4)
	unsigned short taille_avant_coffre =  432/2;
	//Pleins de chiffres hexadécimaux qui me servent pas tant que je fait que le coffre
	//Viendra à changer si je fait autre chose.
	vector<int> la_merde_avant_le_coffre;
	short temp = 0, id_item_act, nb_item_act;
	for (unsigned short rep = 0; rep < taille_avant_coffre; rep++)
	{
		fich_save.read((char *)&temp, sizeof(short));
		la_merde_avant_le_coffre.push_back(temp);
	}
	//La clé c'est l'id en hexa
	//La valeur c'est le nombre d'item dans le coffre
	//C'est possible sachant que un item peux pas être présent plusieurs fois dans le coffre
	//C'est pas comme un coffre Minecraft
	map<unsigned int, unsigned int> coffre;
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
		coffre[id_item_act] = nb_item_act;
	}
	fich_save.close();
	map<unsigned int, unsigned int>::iterator début = coffre.begin(), fin = coffre.end(), it;
	for (it = début; it != fin; it++)
		cout << "Vous avez " << it->second << " " << itemID[it->first - 1] << " dans votre coffre." << endl;
	return 0;
}
















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