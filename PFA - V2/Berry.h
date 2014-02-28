#pragma once

#include <list>
#include "IEntity.h"

class Berry : public IEntity
{
public:
	Berry(void);
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	virtual ~Berry(void);
	void update(Map &);

	//sf::Rect & getCollisionBox(void);

private:
	int									_value;
};