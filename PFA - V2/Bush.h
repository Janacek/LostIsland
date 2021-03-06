#include "Tree.h"
#include "ShadersManager.h"

class Bush : public Tree
{
public:
	Bush();

	void				doAction(AEntity *);
	void				getAction(AEntity *);
	void				Animate(std::string const &);
	void				draw(sf::RenderTexture *, sf::Shader &);
	void				draw(sf::RenderTexture *);
	void				update(Map &);
	Type				getType() const { return BUSH; };
	virtual int			getLife() const;

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);

	sf::Clock			_bushClock;
	float				_oldDt;

	bool				_grown;
	float				_timeToGrow;
	float				_growthTime;
};