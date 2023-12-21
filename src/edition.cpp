#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "saveEditor.hpp"

using namespace std;

unsigned short chercheIdAvecNom(const vector<string> & itemID, const string & nomItem)
{
    unsigned short i;
    for (i = 0; i < itemID.size(); i++)
        if (nomItem == itemID[i])
            return i;
    return 0;
}

bool verifPossItem(map<unsigned short, unsigned short> & coffre, unsigned short itemID)
{
    map<unsigned short, unsigned short>::iterator debut = coffre.begin(), fin = coffre.end(), it;
    for (it = debut; it != fin; it++)
    {
        if (itemID == it->first)
            return true;
        if (itemID == 0)
            return false;
    }
    return false;
}

void ajouterItem(map<unsigned short, unsigned short> & coffre, const string & nomItem, const vector<string> & itemID)
{
    unsigned short idAChercher = chercheIdAvecNom(itemID,nomItem);
    if (verifPossItem(coffre,idAChercher))
    {
        cout << "Erreur, l'item existe dejà dans le coffre, vouliez vous changer la quantite ?" << endl;
        return;
    }
    if (! ajouterUnItemAvecID(coffre,idAChercher))
        cout << "Erreur à l'ajout d'un item" << endl;
    else
        cout << "L'item a bien ete ajoute dans votre coffre !" << endl;
    
}

void ajouterItem(map<unsigned short, unsigned short> & coffre, unsigned short idItem)
{
    if (idItem >= 1533)
    {
        cout << "Erreur, l'id d'item donne est trop grand (max 1532 en decimal ou 05FC en hexadecimal)" << endl;
        return;
    }
    if (verifPossItem(coffre,idItem))
    {
        cout << "Erreur, l'item existe dejà dans le coffre, vouliez vous changer la quantite ?" << endl;
        return;
    }
    if (! ajouterUnItemAvecID(coffre,idItem))
        cout << "Erreur à l'ajout d'un item" << endl;
    else
        cout << "L'item a bien ete ajoute dans votre coffre !" << endl;
}

bool ajouterUnItemAvecID (map<unsigned short, unsigned short> & coffre, unsigned short idItem)
{
    unsigned short qte;
    cout << "Quelle quantite ?" << endl;
    cin >> qte;
    while (qte >= 1000)
    {
        cout << "Quantity too high, enter a lower one: " << endl;
        cin >> qte;
    }
    unsigned short qteTot = coffre[idItem] + qte;
    coffre[idItem] = qteTot;
    unsigned short nbEmplacement = qteTot%99 + 1, i;
    // Sert à supprimer des emplacements de coffre en trop, car si on a + que 99 d'un item,
    // il prend plusieurs slots
    for (i = 0; i < nbEmplacement; i++)
        coffre.erase(coffre.size());
    return true;
}

void changerQte(map<unsigned short, unsigned short> & coffre, unsigned short id)
{
    if (! verifPossItem(coffre,id))
    {
        cerr << "Item wasn't found in your chest" << endl;
        return;
    }
    unsigned short &qte = coffre[id];
    cout << "Current quantity: " << qte << endl;
    cout << "New quantity:" << endl;
    cin >> qte;
    while (qte >= 1000)
    {
        cerr << "Quantity too big" << endl;
        cin >> qte;
    }
}

void changerQte(map<unsigned short, unsigned short> & coffre, const string & name, const vector<string> & itemID)
{
    unsigned short idAChercher = chercheIdAvecNom(itemID,name);
    changerQte(coffre,idAChercher);
}
