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
void chargementCoffre(std::vector<unsigned short> & avant_le_coffre, std::map<unsigned short, unsigned short> & coffre, std::vector<unsigned short> & apres_le_coffre);

// Functions for Edition

// Returns a bool, true true if the item is in the inventory.
bool vérifPossItem(const std::map<unsigned short, unsigned short> & coffre, unsigned short itemID);
// Return the id of an Item from it's name
unsigned short chercheIdAvecNom(const std::vector<std::string> & itemID, const std::string & nomItem);
// Add an item in the chest from it's name
void ajouterItem(std::map<unsigned short, unsigned short> & coffre, const std::string & nomItem, const std::vector<std::string> & itemID);
// Add an item in the chest from it's Id
void ajouterItem(std::map<unsigned short, unsigned short> & coffre, unsigned short idItem);
// Function that truly adds the item.
bool ajouterUnItemAvecID(std::map<unsigned short, unsigned short> & coffre, unsigned short idItem);
// Edit the quantity of an item already in the chest from the id.
void changerQte(std::map<unsigned short, unsigned short> & coffre, unsigned short id);
// Edit the quantity of an item already in the chest from the name.
void changerQte(std::map<unsigned short, unsigned short> & coffre, const std::string & name, const std::vector<std::string> & itemID);

// Save function
void sauvegarde(const std::vector<unsigned short> & avant_le_coffre, const std::map<unsigned short, unsigned short> & coffre, const std::vector<unsigned short> & apres_le_coffre);


#endif