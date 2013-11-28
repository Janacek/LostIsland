#include <list>
#include "IEntity.h"

class Player
{
public:
   void doAction(IEntity* other);
   void getAction(IEntity* other);
   void Animate(std::string const & string_anim);
   int getDamage(void);
   //sf::Rect & getCollisionBox(void);

protected:
private:
   int _life;
   int _damages;
   int _water;
   int _food;
   bool _isSick;
   std::list<IEntity *> _inventory;


};