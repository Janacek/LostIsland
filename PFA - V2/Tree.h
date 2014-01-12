#pragma once

#include <list>
#include "IEntity.h"


class Tree : public IEntity
{
public:
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void Animate(std::string const & string_anim);
	void draw();
	int getDamage(void) const;
	//sf::Rect & getCollisionBox(void);

protected:
private:
	std::list<IEntity *> _inventory;


};