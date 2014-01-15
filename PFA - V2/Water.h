#pragma once

#include <list>
#include "IEntity.h"

class Water : public IEntity
{
public:
	Water(void);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void draw();
	void setPosition(sf::Vector2f &pos);
	void Animate(std::string const & string_anim);
	int getDamage(void) const;
	Type getType() const;
	~Water(void);
	void setPath(std::list<sf::Vector2f > &path);

	sf::Vector2f  getPosition() const;

	//sf::Rect & getCollisionBox(void);

private:
	std::list<sf::Vector2f > _path;
	sf::Vector2f			_pos;
};

