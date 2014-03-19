#pragma once

#include "AEntity.h"

class Gear : public AEntity
{
public:
	Gear();
	virtual ~Gear();

	virtual void loadAnimation(std::string const &, float);
	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
	virtual Type getType() const;
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual void update(Map &);
	virtual int getArmorValue();
	virtual int getWeaponValue();

protected:
	int	_armorValue;
	int _weaponValue;
};