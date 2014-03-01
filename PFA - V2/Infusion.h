#pragma once

#include "AEntity.h"

class Infusion : public AEntity
{
public:
	Infusion();
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	~Infusion(void);
	void update(Map &);
};