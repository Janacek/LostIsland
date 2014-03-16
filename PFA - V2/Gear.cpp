#include "Gear.h"

Gear::Gear()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	_armorValue = 0;
	_weaponValue = 0;
}

Gear::~Gear()
{

}

int Gear::getArmorValue()
{
	return _armorValue;
}

int Gear::getWeaponValue()
{
	return _weaponValue;
}

void Gear::loadAnimation(std::string const &, float)
{
	// no animations to load
}

std::string &Gear::serialize() const
{
	std::string toto;
	return toto;
}

void Gear::deserialize(std::ifstream &) throw (MyException)
{

}

Type Gear::getType() const
{
	return GEAR;
}

void Gear::draw(sf::RenderTexture *, sf::Shader &)
{
	// nothing to draw
}

void Gear::draw(sf::RenderTexture *)
{
	// nothing to draw
}

void Gear::update(Map &)
{
	// nothing to update
}