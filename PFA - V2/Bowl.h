#pragma once

#include "AEntity.h"

class Bowl : public AEntity
{
public:
	Bowl();
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	~Bowl(void);
	void update(Map &);
};