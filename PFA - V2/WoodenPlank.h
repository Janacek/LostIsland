#pragma once

#include <list>
#include "AEntity.h"

class WoodenPlank : public AEntity
{
public:
	WoodenPlank();
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	~WoodenPlank(void);
	void update(Map &);
};