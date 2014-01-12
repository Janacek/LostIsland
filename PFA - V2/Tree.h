#pragma once

#include <list>
#include "IEntity.h"


class Tree : public IEntity
{
public:
   void doAction(IEntity* other);
   void getAction(IEntity* other);
   void Animate(std::string const & string_anim);
   int getDamage(void) const;
   Type getType() const;
   //sf::Rect & getCollisionBox(void);

protected:
private:
	int _damages;


};