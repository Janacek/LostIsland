#pragma once

#include <list>
#include "IEntity.h"
#include "Singleton.h"
#include "ImageSingleton.h"
#include <iostream>


class Tree : public IEntity
{
public:
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void Animate(std::string const & string_anim);
	void draw();
	Type getType() const;
	int getDamage(void) const;
	void setPosition(sf::Vector2f &);
	sf::Vector2f const &getPosition() const;
	//sf::Rect & getCollisionBox(void);

protected:
private:
	int				_damages;
	sf::Vector2f	_position;


};