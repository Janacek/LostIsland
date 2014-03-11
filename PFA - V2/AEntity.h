#pragma once

#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>
#include						<list>
#include						"Map.h"
#include						"SerializeTools.h"

enum Type
{
	TREE,
	CUT_TREE,
	WOOD,
	WATER,
	WOODEN_PLANK,
	BUCKET,
	BOWL,
	SILEX,
	JACKET,
	FABRIC,
	FUR,
	PANTS,
	ROPE,
	BERRY,
	HERB,
	STEW,
	MUSHROOM,
	INFUSION,
	WATERBUCKET,
	SWORD,
	WATER_WALKABLE,
	MEAT,
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
	PLAYER_INFOS_BACKGROUND,
	SELECTED_ICON,
	BADTYPE,
	CAMPFIRE,
	WATER_ANIM,
	MENU_SCREEN,
	HARMLESS_ANIMAL,
	SHEEP,
	PICKABLE_GRASS,
	PICKABLE_MUSHROOM,
};

inline const char* typetoString(Type v)
{
	//TODO rajouter les autres
	switch (v)
	{
	case TREE:   return "TREE";
	case SWORD:  return "SWORD";
	case ROCK:	 return "ROCK";
	case CUT_TREE: return "CUT_TREE";
	case WATER:		return "WATER";
	case WOOD:		return "WOOD";
	case WOODEN_PLANK:	return "WOODEN_PLANK";
	case BUCKET:		return "BUCKET";
	case BOWL:		return "BOWL";
	case CAMPFIRE:		return "CAMPFIRE";
	case SILEX:		return "SILEX";
	case FABRIC:		return "FABRIC";
	case FUR:		return "FUR";
	case HERB:		return "HERB";
	case STEW:		return "STEW";
	case MUSHROOM:		return "MUSHROOM";
	case INFUSION:		return "INFUSION";
	case ROPE:		return "ROPE";
	case WATERBUCKET:		return "WATERBUCKET";
	case BERRY:		return "BERRY";
	default:      return "BADTYPE";
	}
}


static int AEntityId = 0;

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


	virtual std::string &serialize() const = 0;
	virtual void deserialize(std::ifstream &) throw(MyException) = 0;


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
	virtual sf::FloatRect  getBoxCollider() const;							
	virtual sf::Vector2f const getPosDisp() const;
	virtual int getLife() const;
	virtual void setLife(int);
	int getId() const;
	void setId(int);
	bool getIsSelected() const;
	void setIsSelected(bool);
	void setIsDead(bool);
	bool getIsDead() const;
	void setIsActionOver(bool);
	bool getIsActionOver() const;

	AEntity(float pathtogo,
		bool isAMovingEntity,
		sf::Vector2f pos,
		int dmg,
		sf::FloatRect boxcollider,
		int life) ;

protected:
	float								_pathToGo;
	bool								_isSelected;
	bool								_isActionOver;
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
	sf::Vector2f						_posDisp;
	bool								_isDead;
};
