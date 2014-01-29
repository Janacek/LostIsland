#pragma once

#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>
#include						<list>

enum Type
{
	TREE,
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
	BUSH,
	BUSH_FRUITS,
	PALMTREE,
}; //ok j'ai enlevé le close_button

class IEntity
{
public:
	virtual void doAction(IEntity* other) = 0;
	virtual void getAction(IEntity* other) = 0;
	virtual void loadAnimation(std::string const & string_anim, float speed) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void setPath(std::list<std::pair<float, float> >&) = 0;
	virtual void setPosition(sf::Vector2f &pos) = 0;
	virtual sf::Vector2f  getPosition() const = 0;
	virtual int getDamage(void) const = 0;
	virtual Type getType() const = 0;
	//sf::Rect &getCollisionBox(void);

protected:
private:

};
