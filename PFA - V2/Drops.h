#pragma once

#include		<vector>
#include		"IEntity.h"
#include		"ImageSingleton.h"
#include		"ShadersManager.h"

class Drops : public IEntity
{
public:
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual void update(Map &);
	Type getType() const;
	bool getIsMoving() const { return false; }
	void setPath(std::list<std::pair<float, float> >&  path);
	float getPathToGo() const { return 0.f; }
	void setPathToGo(float f) { (void)f; }
	void addToPathToGo(float f) { (void)f; }
	bool const getSelected() const{ return true; }
	bool const getIsPathFound() const { return false; }
	void setIsPathFound(bool n) { (void)n; }
	bool getIsStopped() const{ return false; }

	void setPosition(sf::Vector2f &);
	sf::Vector2f  getPosition() const;
	bool getIsAMovingEntity() const{ return false; }

	std::vector<IEntity *>				&getDrops();

	//sf::Rect & getCollisionBox(void);

protected:
	std::list<std::pair<float, float> > _path;
	sf::Vector2f						_position;
	std::vector<IEntity *>				_drops;
};