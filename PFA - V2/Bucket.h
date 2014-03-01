#pragma once

#include "AEntity.h"

class Bucket : public AEntity
{
public:
	Bucket();
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	~Bucket(void);
	void update(Map &);
};