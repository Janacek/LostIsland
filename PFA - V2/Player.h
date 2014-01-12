#pragma once
#include <vector>
#include "IEntity.h"
#include "Compartment.h"
#include "Water.h"

class Player : public IEntity
{
public:
	Player();
   void doAction(IEntity* other);
   void getAction(IEntity* other);
   void drink(Water *);
   std::string const &getName() const;
   void setName(std::string const &);
   void Animate(std::string const & string_anim);
   int getDamage(void) const;
   Type getType() const;
   void addCompartment(sf::RectangleShape &);
   void addEntityInInventory(IEntity *entity);
   //sf::Rect & getCollisionBox(void);

   //TODO : Changer en compartments pour l'inventaire
   std::vector<Compartment *> _compartments;
  // std::vector<IEntity *> _inventary;
protected:
private:

	unsigned int _sizeInventory;
	std::string _name;
   int _life;
   int _damages;
   int _water;
   int _food;
   bool _isSick;
  
};