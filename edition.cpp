#include <string>
#include <vector>
#include <map>
#include <iostream>

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

bool verifPossItem(map<unsigned short, unsigned short> & coffre, unsigned short itemID)
{
    map<unsigned short, unsigned short>::iterator debut = coffre.begin(), fin = coffre.end(), it;
    for (it = debut; it != fin; it++)
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
    cout << "Avant" << endl;
    cout << "Quelle quantite ?" << endl;
    cin >> qte;
    cout << "Apres" << endl;
    while (qte >= 1000)
    {
        cout << "Quantite trop haute, veuillez en rentree une plus petite: " << endl;
        cin >> qte;
    }
    unsigned short qteTot = coffre[idItem] + qte;
    coffre[idItem] = qteTot;
    unsigned short nbEmplacement = qteTot%99 + 1, i;
    //Sert à supprimer des emplacements de coffre en trop, car si on a + que 99 d'un item,
    //il prend plusieurs slots
    for (i = 0; i < nbEmplacement; i++)
        coffre.erase(coffre.size());
    return true;
}

void changerQte(map<unsigned short, unsigned short> & coffre)
{
    unsigned short idItem;
    cout << "Quel item ?" << endl;
    cin >> idItem;
    if (! verifPossItem(coffre,idItem))
    {
        cout << "Erreur, l'item n'a pas pu être trouvé dans le coffre" << endl;
        return;
    }
    unsigned short &qte = coffre[idItem];
    cout << "Quantite actuelle: " << qte << endl;
    cout << "Nouvelle quantite :" << endl;
    cin >> qte;
    while (qte >= 1000)
    {
        cout << "Erreur, quantite trop grande" << endl;
        cin >> qte;
    }
}
