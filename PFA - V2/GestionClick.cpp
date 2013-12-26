#include "GestionClick.h"


GestionClick::GestionClick(void)
{
	this->_enumToString[INVENTORY] = "Inventory";
	this->_enumToString[STUFF] = "Stuff";
	this->_enumToString[CRAFTING] = "Crafting";
	this->_enumToString[NONE] = "NONE";
	createCorrelationTable();
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

void	GestionClick::createCorrelationTable()
{
	createInventoryTable();
	createStuffTable();
	createCraftingTable();
}

void	GestionClick::createCraftingTable()
{
	std::map<Screens, void (GestionClick::*)(s_action&, s_action&)> tmp;


	tmp[STUFF] = &GestionClick::add;
	tmp[CRAFTING] = &GestionClick::swap;
	tmp[INVENTORY] = &GestionClick::add;
	tmp[NONE] = &GestionClick::drop;

	this->_correlationTable[CRAFTING] = tmp;
}

void	GestionClick::createInventoryTable()
{
	std::map<Screens, void (GestionClick::*)(s_action&, s_action&)> tmp;


	tmp[STUFF] = &GestionClick::add;
	tmp[CRAFTING] = &GestionClick::add;
	tmp[INVENTORY] = &GestionClick::swap;
	tmp[NONE] = &GestionClick::drop;

	this->_correlationTable[INVENTORY] = tmp;
}

void	GestionClick::createStuffTable()
{
	std::map<Screens, void (GestionClick::*)(s_action&, s_action&)> tmp;

	tmp[STUFF] = &GestionClick::swap;
	tmp[CRAFTING] = &GestionClick::add;
	tmp[INVENTORY] = &GestionClick::add;
	tmp[NONE] = &GestionClick::drop;

	this->_correlationTable[STUFF] = tmp;
}

void	GestionClick::callFunction(s_action &a1, s_action &a2)
{
	std::map<Screens, void (GestionClick::*)(s_action&, s_action&)> tmp;
	tmp = this->_correlationTable[STUFF];
	_caller = tmp[STUFF];
	(this->*_caller)(a1, a2);
}