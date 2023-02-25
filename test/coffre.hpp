#ifndef COFFRE_HPP
#define COFFRE_HPP

#include <string>
#include <iostream>
#include <vector>

class ItemID;

class Item {
	unsigned short m_itemID;
	unsigned short m_nbItem;
public:
	Item(unsigned short id, unsigned short nb = 0);
	std::string getName(std::vector<std::string> & itemID);
	friend std::ostream &operator<<(std::ostream & os, Item & it);
};

std::ostream &operator<<(std::ostream & os, Item & it);

#endif // COFFRE_HPP