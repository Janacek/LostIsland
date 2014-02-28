#pragma once

#include		<vector>
#include		"IEntity.h"


class Drops : public IEntity
{
public:
	Drops();
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual void update(Map &);
	Type getType() const;


	std::list<IEntity *>				&getDrops();
	void								addDrop(IEntity *);
	void								addDrop(std::list<IEntity *>);
	//sf::Rect & getCollisionBox(void);

protected:
	std::list<IEntity *>				_drops;
};