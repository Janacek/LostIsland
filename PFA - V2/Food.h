#pragma once

#include <list>
#include "IEntity.h"

class Food :public IEntity
{
public:
	Food(void);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void setPath(std::list<sf::Vector2f > &);

	void Animate(std::string const & string_anim);
	int getDamage(void) const;
	void draw();
	void setPosition(sf::Vector2f &pos);
	sf::Vector2f  getPosition() const;

	Type getType() const;
	~Food(void);
private:
	std::list<sf::Vector2f > _path;
	sf::Vector2f			_pos;

};

