#include "coffre.hpp"

#include <iostream>

using namespace std;

Item::Item(unsigned short id, unsigned short nb)
	:m_itemID{id}, m_nbItem{nb}
{
	cout << *this << endl;
}

string Item::getName(vector<string> & itemID)
{
	return itemID.at(m_itemID - 2);
}

std::ostream & operator<<(std::ostream & os, Item & it)
{
	return os << it.m_itemID << " " << it.m_nbItem; 
}