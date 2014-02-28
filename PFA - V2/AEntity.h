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

class AEntity
{
public:
	virtual void doAction(AEntity* other) = 0;										// reste
	virtual void getAction(AEntity* other) = 0;										// reste
	virtual void loadAnimation(std::string const & string_anim, float speed) = 0;	// reste
	virtual void draw(sf::RenderTexture *) = 0;										// reste
	virtual void draw(sf::RenderTexture *, sf::Shader &) = 0;						// reste
	virtual void update(Map &) = 0;													// reste
	virtual Type getType() const = 0;												// reste





	virtual void setPath(std::list<std::pair<float, float> >&);
	virtual std::list<std::pair<float, float> > getPath() const;	
	virtual sf::Vector2f  getPosition() const;
	virtual void setPosition(sf::Vector2f &);
	virtual int getDamage(void) const;
	virtual bool getIsMoving() const;
	virtual float getPathToGo() const;
	virtual void setPathToGo(float f);
	virtual void addToPathToGo(float f);
	virtual bool const getSelected() const;
	virtual bool const getIsPathFound() const;
	virtual void setIsPathFound(bool);
	virtual bool getIsStopped() const;
	virtual bool getIsAMovingEntity() const;
	virtual sf::FloatRect  getBoxCollider() const;							// enlève
	virtual int getLife() const;
	virtual void setLife(int);
	int getId() const;
	void setId(int);
	bool getIsSelected() const;
	void setIsSelected(bool);

	AEntity(float,
		bool,
		sf::Vector2f,
		int,
		sf::FloatRect,
		int);

protected:
	float								_pathToGo;
	bool								_isSelected;
	bool								_isMoving;
	bool								_isPathFound;
	bool								_isAMovingEntity;
	bool								_isStopped;
	std::list<std::pair<float, float>>	_path;
	sf::Vector2f						_position;
	int									_damages;
	sf::FloatRect						_boxCollider;
	int									_life;
	int									_id;

private:

};
