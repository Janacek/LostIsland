#pragma once

#include <list>
#include "IEntity.h"

class Wood : public IEntity
{
public:
	Wood(void);
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	~Wood(void);
	void update(Map &);
private:
};

