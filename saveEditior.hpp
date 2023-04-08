#ifndef saveEditor

#include <string>
#include <vector>
#include <map>

// Functions for loading

// Endian Swap
void swapByteOrder(unsigned short & us);
// Load the file with the correspondance between id and name
void chargementID(std::vector<std::string> & itemID);
// Load the chest in memory
void chargementCoffre(std::vector<unsigned short> & la_merde_avant_le_coffre, std::map<unsigned short, unsigned short> & coffre, std::vector<unsigned short> & la_merde_apres_le_coffre);

// Functions for Edition

// Returns a bool, true true if the item is in the inventory.
bool vérifPossItem(std::map<unsigned short, unsigned short> & coffre, unsigned short itemID);
// Return the id of an Item from it's name
unsigned short chercheIdAvecNom(std::vector<std::string> & itemID, std::string & nomItem);
// Add an item in the chest from it's name
void ajouterItem(std::map<unsigned short, unsigned short> & coffre, std::string & nomItem, std::vector<std::string> & itemID);
// Add an item in the chest from it's Id
void ajouterItem(std::map<unsigned short, unsigned short> & coffre, unsigned short idItem);
// Function that truly adds the item.
bool ajouterUnItemAvecID (std::map<unsigned short, unsigned short> & coffre, unsigned short idItem);
// Edit the quantity of an item already in the chest.
void changerQte(std::map<unsigned short, unsigned short> & coffre);

// Save function
void sauvegarde(std::vector<unsigned short> & la_merde_avant_le_coffre, std::map<unsigned short, unsigned short> & coffre, std::vector<unsigned short> & la_merde_apres_le_coffre);


#endif