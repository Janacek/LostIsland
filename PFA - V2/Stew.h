#pragma once

#include "AEntity.h"

class Stew : public AEntity
{
public:
	Stew();
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	~Stew(void);
	void update(Map &);
};