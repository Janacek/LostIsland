#pragma once

#include "IEntity.h"

class Food :public IEntity
{
public:
	Food(void);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void Animate(std::string const & string_anim);
	int getDamage(void) const;
	void draw();
	void setPosition(sf::Vector2f &pos);
	Type getType() const;
	~Food(void);
};

