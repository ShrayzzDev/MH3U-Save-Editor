#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <windows.h>

#include "saveEditior.hpp"

using namespace std;

unsigned short chercheIdAvecNom(vector<string> & itemID, string & nomItem)
{
    unsigned short i;
    for (i = 0; i < itemID.size(); i++)
        if (nomItem == itemID[i])
            return i;
    return 0;
}

bool vérifPossItem(map<unsigned short, unsigned short> & coffre, unsigned short itemID)
{
    map<unsigned short, unsigned short>::iterator début = coffre.begin(), fin = coffre.end(), it;
    for (it = début; it != fin; it++)
    {
        if (itemID == it->first)
            return true;
        if (it->first == 0)
            return false;
    }
    return false;
}

void ajouterItem(map<unsigned short, unsigned short> & coffre, string & nomItem, vector<string> & itemID)
{
    unsigned short idAChercher = chercheIdAvecNom(itemID,nomItem);
    if (vérifPossItem(coffre,idAChercher))
    {
        cout << "Erreur, l'item existe déjà dans le coffre, vouliez vous changer la quantité ?" << endl;
        return;
    }
    if (! ajouterUnItemAvecID(coffre,idAChercher))
        cout << "Erreur à l'ajout d'un item" << endl;
    else
        cout << "L'item a bien été ajouté dans votre coffre !" << endl;
    
}

void ajouterItem(map<unsigned short, unsigned short> & coffre, unsigned short idItem)
{
    if (idItem >= 1533)
    {
        cout << "Erreur, l'id d'item donné est trop grand (max 1532 en décimal ou 05FC en hexadécimal)" << endl;
        return;
    }
    if (vérifPossItem(coffre,idItem))
    {
        cout << "Erreur, l'item existe déjà dans le coffre, vouliez vous changer la quantité ?" << endl;
        return;
    }
    if (! ajouterUnItemAvecID(coffre,idItem))
        cout << "Erreur à l'ajout d'un item" << endl;
    else
        cout << "L'item a bien été ajouté dans votre coffre !" << endl;
}

bool ajouterUnItemAvecID (map<unsigned short, unsigned short> & coffre, unsigned short idItem)
{
    unsigned short qte;
    cout << "Avant" << endl;
    cout << "Quelle quantité ?" << endl;
    cin >> qte;
    cout << "Après" << endl;
    while (qte >= 1000)
    {
        cout << "Quantité trop haute, veuillez en rentrée une plus petite: " << endl;
        cin >> qte;
    }
    //nbEmplacement sert à savoir le nombre de slot que l'item va prendre
    //car un slot contient max 99 fois un item, mais un item peut être sur plusieurs slots
    unsigned short nbEmplacement = (qte % 99) + 1, i ;
    coffre[idItem] = 0;
    coffre.erase(coffre.size());
    //En rajoutant un item, on augemente la taille du coffre par 1, sauf qu'il a une taille limité
    //Donc on supprime le dernier élément, qui logiquement est à 0, donc n'impactera logiquement pas 
    //Les items stockés dans le coffre
    for (i = 0; i < nbEmplacement; i++)
    {
        cout << "test" << endl;
        if (qte > 99)    
        {    
            coffre[idItem] += 99;
            qte -= 99;
        } else 
            coffre[idItem] += qte;
    }
    return true;
}