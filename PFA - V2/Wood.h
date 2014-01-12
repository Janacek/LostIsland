	#pragma once

#include "IEntity.h"

class Wood : public IEntity
{
public:
	Wood(void);
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	virtual void Animate(std::string const & string_anim);
	virtual int getDamage(void) const;
	virtual Type getType() const;
	~Wood(void);
};

