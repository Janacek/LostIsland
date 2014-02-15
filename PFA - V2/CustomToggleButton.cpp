#include "CustomToggleButton.h"


CustomToggleButton::CustomToggleButton(Player *p, Compartment *c) : _player(p), _ressources(c)
{
	this->_button = sfg::ToggleButton::Create();
	if (c != NULL)
	{
		this->_img = sfg::Image::Create(c->getImage());
		this->_button->SetImage(this->_img);
	}
	else
		this->_img = NULL;
}

bool CustomToggleButton::isEmpty() const
{
	return this->_ressources == NULL || this->_ressources->getSize() == 0 ? true : false;
}

std::list<IEntity *>CustomToggleButton::getEntities()
{
	if (this->_ressources != NULL)
		return this->_ressources->getElements();
}

Compartment *CustomToggleButton::getCompartment()
{
	return this->_ressources;
}

Type CustomToggleButton::getType() const
{
	if (this->_ressources->getSize() == 0)
		return BADTYPE;
	return this->_ressources->getType();
}

Player *CustomToggleButton::getPlayer()
{
	return this->_player;
}

CustomToggleButton::~CustomToggleButton()
{
}
