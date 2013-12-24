#include "GestionClick.h"


GestionClick::GestionClick(void)
{
	this->_enumToString[INVENTORY] = "Inventory";
	this->_enumToString[STUFF] = "Stuff";
		this->_enumToString[CRAFTING] = "Crafting";
	this->_enumToString[NONE] = "NONE";
}

void	GestionClick::swap(s_action&a, s_action&b)
{
	std::cout << "SWAP between " << this->_enumToString[a._screen] << "and " <<  this->_enumToString[b._screen] << std::endl;
}

void	GestionClick::add(s_action&a, s_action&b)
{
	std::cout << "add between " << this->_enumToString[a._screen] << "and " <<  this->_enumToString[b._screen] << std::endl;
}

void	GestionClick::drop(s_action&a, s_action&b)
{
	std::cout << "drop between " << this->_enumToString[a._screen] << "and " <<  this->_enumToString[b._screen] << std::endl;
}

GestionClick::~GestionClick(void)
{
}
