#include "Tree.h"
#include "ShadersManager.h"

class Bush : public Tree
{
public:
	Bush();

	void				doAction(IEntity *);
	void				getAction(IEntity *);
	void				Animate(std::string const &);
	void				draw(sf::RenderTexture *, sf::Shader &);
	void				draw(sf::RenderTexture *);
	void				update(Map &);

	sf::Clock			_bushClock;
	float				_oldDt;

	bool				_grown;
	float				_timeToGrow;
	float				_growthTime;
};