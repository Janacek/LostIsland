#pragma once

#include "IEntity.h"

class Water : public IEntity
{
public:
	Water(void);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void Animate(std::string const & string_anim);
	int getDamage(void) const;
	Type getType() const;
	~Water(void);
};

