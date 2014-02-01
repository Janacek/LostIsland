#include "GestionClick.h"

GestionClick::GestionClick()
{
	this->_canDrop = false;
	this->_lastCompartment = NULL;
}

void GestionClick::leftPress(int index, Player *p, sfg::Image::Ptr img)
{
	this->_canDrop = false;
	this->_leftClickPressed._compartment = p->getCompartment(index);
	if (this->_leftClickPressed._compartment != NULL)
		this->_lastCompartment = this->_leftClickPressed._compartment;
	this->_leftClickPressed._img = img;
}

void GestionClick::leftRelease(int index, Player *p, sfg::Image::Ptr img)
{
	//this->_leftClickReleased.reset();
	this->_leftClickReleased._compartment = p->getCompartment(index);
	this->_leftClickReleased._img = img;
	swap();
}

void GestionClick::dump(int index, Player *p)
{
	if (p != NULL && p->getCompartment(index) != NULL)
		std::cout << "DUMP : index : " << index << " player : " << p->getName() << " ressource : " << p->getCompartment(index)->getType() << std::endl;
}

void GestionClick::clearLastCompartment()
{
	this->_lastCompartment = NULL;
}

void GestionClick::drop()
{
	if (this->_leftClickPressed._compartment != NULL)
	{
		std::cout << "La si on lache le click il faut poser la ressource" << std::endl;
		this->_canDrop = true;
		return;
	}
	this->_leftClickPressed.reset();
}

void GestionClick::swap()
{
	if (this->_leftClickPressed._compartment == NULL || this->_leftClickReleased._compartment == NULL)
	{
		this->_leftClickPressed.reset();
		this->_leftClickReleased.reset();
		std::cout << "Je ne swap pas, erreur (on ne peux pas swap avec case vide)" << std::endl;
		return;
	}
	Compartment tmp = *this->_leftClickPressed._compartment;

	*this->_leftClickPressed._compartment = *this->_leftClickReleased._compartment;
	*this->_leftClickReleased._compartment = tmp;
	
	this->_leftClickPressed._img->SetImage(this->_leftClickPressed._compartment->getImage());
	this->_leftClickReleased._img->SetImage(this->_leftClickReleased._compartment->getImage());

	this->_leftClickPressed.reset();
	this->_leftClickReleased.reset();
}

s_action GestionClick::canDrop()
{
	s_action tmp = this->_leftClickPressed;
	tmp._compartment = this->_lastCompartment;
	if (this->_canDrop == false)
		tmp._compartment = NULL;
	return tmp;
}

GestionClick::~GestionClick()
{

}