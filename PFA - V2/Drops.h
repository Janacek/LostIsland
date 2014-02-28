#pragma once

#include		<vector>
#include		"AEntity.h"


class Drops : public AEntity
{
public:
	Drops();
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual void update(Map &);
	Type getType() const;


	std::list<AEntity *>				&getDrops();
	void								addDrop(AEntity *);
	void								addDrop(std::list<AEntity *>);
	//sf::Rect & getCollisionBox(void);

protected:
	std::list<AEntity *>				_drops;
};