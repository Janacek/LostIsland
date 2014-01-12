#pragma once

#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>

enum Type
{
	WOOD,
	WATER,
	FOOD,
	PLAYER,
	SABLE,
	LAC,
	GRASS,
	SAVANNA,
	FOREST,
	SNOW,
};

class IEntity
{
public:
   virtual void doAction(IEntity* other) = 0;
   virtual void getAction(IEntity* other) = 0;
   virtual void Animate(std::string const & string_anim) = 0;
   virtual void draw() = 0;
   virtual void setPosition(sf::Vector2f &pos) = 0;
   virtual int getDamage(void) const = 0;
   virtual Type getType() const = 0;
   //sf::Rect &getCollisionBox(void);

protected:
private:

};
