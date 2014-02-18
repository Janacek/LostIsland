#pragma once

#include		<vector>
#include		"IEntity.h"


class Drops : public IEntity
{
public:
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	virtual int getDamage(void) const { return 0; };
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
	std::list<std::pair<float, float>> getPath() const { return this->_path; };

	std::list<IEntity *>				&getDrops();
	void								addDrop(IEntity *);
	void								addDrop(std::list<IEntity *>);
	//sf::Rect & getCollisionBox(void);

protected:
	std::list<std::pair<float, float> > _path;
	sf::Vector2f						_position;
	std::list<IEntity *>				_drops;
};