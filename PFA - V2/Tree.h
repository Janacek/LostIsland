#include <list>
#include "IEntity.h"


class Tree
{
public:
   void doAction(IEntity* other);
   void getAction(IEntity* other);
   void Animate(std::string const & string_anim);
   int getDamage(void);
   //sf::Rect & getCollisionBox(void);

protected:
private:
   std::list<IEntity *> _inventory;


};