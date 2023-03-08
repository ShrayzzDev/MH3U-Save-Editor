#ifndef saveEditor

#include <string>
#include <vector>
#include <map>

//Fonctions pour le chargement

//Endian Swap
void swapByteOrder(short & us);
//Charge le fichier qui fait correspondre id et nom des items
void chargementID(std::vector<std::string> & itemID);
//Charge le coffre dans le fichier de sauvegarde
void chargementCoffre(std::vector<unsigned short> & la_merde_avant_le_coffre, std::map<unsigned short, unsigned short> & coffre);

//Fonctions pour l'édition

//Renvoie un bool, true si l'objet est déjà dans le coffre.
bool vérifPossItem(std::map<unsigned short, unsigned short> & coffre, unsigned short itemID);

//Renvoie l'id d'un Item à partir de son nom
unsigned short chercheIdAvecNom(std::vector<std::string> & itemID, std::string & nomItem);

//Ajoute un item dans le coffre à partir du nom de l'item
void ajouterItem(std::map<unsigned short, unsigned short> & coffre, std::string & nomItem, std::vector<std::string> & itemID);

//Ajoute un item dans le coffre à partir de l'id de l'item
void ajouterItem(std::map<unsigned short, unsigned short> & coffre, unsigned short idItem);

//Ajoute concrétement l'item dans le coffre, renvoie un bool (true si ça marche bien, false sinon)
bool ajouterUnItemAvecID (std::map<unsigned short, unsigned short> & coffre, unsigned short idItem);

#endif