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

void CustomToggleButton::empty()
{
	if (this->_button->GetImage() != NULL)
		this->_button->GetImage()->Show(false);
	this->setCompartment(NULL);
	this->_player = NULL;
}

bool CustomToggleButton::isEmpty() const
{
	return this->_ressources == NULL || this->_ressources->getSize() == 0 ? true : false;
}

void CustomToggleButton::setCompartment(Compartment *comp)
{
	this->_ressources = comp;
	if (comp != NULL)
	{
		this->_img = sfg::Image::Create(comp->getImage());
		this->_button->SetImage(this->_img);
	}
	else
	{
		if (this->_button->GetImage() != NULL)
			this->_button->GetImage()->Show(false);
	}
}

std::list<AEntity *>CustomToggleButton::getEntities()
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
