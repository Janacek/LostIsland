#include "CustomToggleButton.h"


CustomToggleButton::CustomToggleButton(Player *p, Compartment *c) : _player(p), _ressources(c)
{
	this->_nbrRessources = 0;
	this->_button = sfg::ToggleButton::Create();
	this->_label = sfg::Label::Create("");
	this->_label->SetRequisition(sf::Vector2f(180.f, 10.f));
	this->_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	if (c != NULL)
	{
		this->_img = sfg::Image::Create(c->getImage());
		this->_button->SetImage(this->_img);
	}
	else
		this->_img = NULL;
	this->setLabelText(c);
	this->_box->Pack(this->_button);
	this->_box->PackEnd(this->_label);
}

void CustomToggleButton::updateLabel()
{
	this->_nbrRessources = this->_ressources->getSize();
	this->setLabelText(this->_ressources);
}

void	CustomToggleButton::setLabelText(Compartment *comp)
{
	if (comp != NULL)
	{
		std::ostringstream os;
		std::string type = typetoString(comp->getType());
		std::transform(type.begin() + 1, type.end(), type.begin() + 1, ::tolower);
		std::string txt = type;
		txt += " : ";
		os << this->_nbrRessources;
		txt += os.str();
		this->_label->SetText(txt);
	}
	else
	{
		this->_label->SetText("");
		this->_nbrRessources = 0;
	}
		
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

void CustomToggleButton::setCompartment(Compartment *comp, int nbr)
{
	this->_ressources = comp;
	if (nbr != 0)
		this->_nbrRessources = nbr;
	else
	{
		if (this->_ressources != NULL)
			this->_nbrRessources = comp->getSize();
		else
			this->_nbrRessources = 0;
	}
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
	this->setLabelText(comp);
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
