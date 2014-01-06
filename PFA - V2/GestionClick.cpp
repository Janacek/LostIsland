#include "GestionClick.h"

GestionClick::GestionClick(void)
{
	this->_enumToString[INVENTORY] = "Inventory";
	this->_enumToString[STUFF] = "Stuff";
	this->_enumToString[CRAFTING] = "Crafting";
	this->_enumToString[GAMESCREEN] = "GameScreen";
	createCorrelationTable();
}

void	GestionClick::swap(s_action&a, s_action&b)
{
	//meme type d'objet, on ajoute au lieu de swap
	if (a._compartment->_elements.size() > 0 && b._compartment->_elements.size() > 0 && a._compartment->_elements.front()->getType() ==  b._compartment->_elements.front()->getType())
	{
		*b._compartment += *a._compartment;
		a._compartment->emptyCompartment();
	}
	else
	{
		Compartment tmp(sf::Vector2f(0, 0));

		tmp = *b._compartment;
		*b._compartment = *a._compartment;
		*a._compartment = tmp;
	}
	std::cout << "SWAP between " << this->_enumToString[a._screen] << " and " <<  this->_enumToString[b._screen] << std::endl;
	a.reset();
	b.reset();
}

void	GestionClick::add(s_action&a, s_action&b)
{
	//meme type d'objet, on ajoute au lieu de swap
	if (a._compartment->_elements.size() > 0 && b._compartment->_elements.size() > 0 && a._compartment->_elements.front()->getType() ==  b._compartment->_elements.front()->getType())
	{
		*b._compartment += *a._compartment;
		a._compartment->emptyCompartment();
	}
	else
	{
		Compartment tmp(sf::Vector2f(0, 0));

		tmp = *b._compartment;
		*b._compartment = *a._compartment;
		*a._compartment = tmp;
	}
	std::cout << "add between " << this->_enumToString[a._screen] << " and " <<  this->_enumToString[b._screen] << std::endl;
	a.reset();
	b.reset();
}

void	GestionClick::drop(s_action&a, s_action&b)
{
	Compartment *tmp = a._compartment;
	tmp->emptyCompartment();
	std::cout << "drop between " << this->_enumToString[a._screen] << " and " <<  this->_enumToString[b._screen] << std::endl;
	a.reset();
	b.reset();
	std::cout << "Mettre la ressource par terre" << std::endl;
}

void GestionClick::doNothing(s_action&a, s_action&b)
{
	std::cout << "Mauvais drag and drop" << std::endl;
	a.reset();
	b.reset();
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
	tmp[GAMESCREEN] = &GestionClick::drop;
	tmp[NONE] = &GestionClick::doNothing;

	this->_correlationTable[CRAFTING] = tmp;
}

void	GestionClick::createInventoryTable()
{
	std::map<Screens, void (GestionClick::*)(s_action&, s_action&)> tmp;


	tmp[STUFF] = &GestionClick::add;
	tmp[CRAFTING] = &GestionClick::add;
	tmp[INVENTORY] = &GestionClick::swap;
	tmp[GAMESCREEN] = &GestionClick::drop;
	tmp[NONE] = &GestionClick::doNothing;

	this->_correlationTable[INVENTORY] = tmp;
}

void	GestionClick::createStuffTable()
{
	std::map<Screens, void (GestionClick::*)(s_action&, s_action&)> tmp;

	tmp[STUFF] = &GestionClick::swap;
	tmp[CRAFTING] = &GestionClick::add;
	tmp[INVENTORY] = &GestionClick::add;
	tmp[GAMESCREEN] = &GestionClick::drop;
	tmp[NONE] = &GestionClick::doNothing;

	this->_correlationTable[STUFF] = tmp;
}

void	GestionClick::callFunction(s_action &a1, s_action &a2)
{
	std::map<Screens, void (GestionClick::*)(s_action&, s_action&)> tmp;
	tmp = this->_correlationTable[a1._screen];
	_caller = tmp[a2._screen];
	(this->*_caller)(a1, a2);
}