#pragma once

#include <list>
#include "AEntity.h"

class Berry : public AEntity
{
public:
	Berry(void);
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	virtual ~Berry(void);
	void update(Map &);

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
	//sf::Rect & getCollisionBox(void);

private:
	int									_value;
};