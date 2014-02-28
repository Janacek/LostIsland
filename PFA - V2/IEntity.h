#pragma once

#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>
#include						<list>
#include						"Map.h"

enum Type
{
	TREE,
	CUT_TREE,
	WOOD,
	WATER,
	WATER_WALKABLE,
	FOOD,
	PLAYER,
	BUNNY,
	SABLE,
	LAC,
	GRASS,
	SAVANNA,
	FOREST,
	SNOW,
	BUSH,
	BUSH_FRUITS,
	CUT_PALMTREE,
	PALMTREE,
	ROCK,
	ROCK_BROKEN,
	DROPS,
	BERRY,
	PLAYER_INFOS_BACKGROUND,
	SELECTED_ICON,
	BADTYPE,
	CAMPFIRE,
};

static int IEntityId = 0;

class IEntity
{
public:
	virtual void doAction(IEntity* other) = 0;
	virtual void getAction(IEntity* other) = 0;
	virtual void loadAnimation(std::string const & string_anim, float speed) = 0;
	virtual void draw(sf::RenderTexture *) = 0;
	virtual void draw(sf::RenderTexture *, sf::Shader &) = 0;
	virtual void update(Map &) = 0;
	virtual void setPath(std::list<std::pair<float, float> >&) = 0;
	virtual std::list<std::pair<float, float> > getPath() const = 0;
	virtual void setPosition(sf::Vector2f &pos) = 0;
	virtual sf::Vector2f  getPosition() const = 0;
	virtual int getDamage(void) const = 0;
	virtual Type getType() const = 0;
	virtual bool getIsMoving() const = 0;
	virtual float getPathToGo() const = 0;
	virtual void setPathToGo(float f) = 0;
	virtual void addToPathToGo(float f) = 0;
	virtual bool const getSelected() const = 0;
	virtual bool const getIsPathFound() const = 0;
	virtual void setIsPathFound(bool)  = 0;
	virtual bool getIsStopped() const = 0;
	virtual bool getIsAMovingEntity() const = 0;
	virtual sf::FloatRect getBoxCollider() const = 0;
	virtual int getLife() const = 0;
	int								_id;

protected:
private:

};
