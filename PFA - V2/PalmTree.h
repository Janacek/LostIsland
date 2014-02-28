#include "Tree.h"
#include "ShadersManager.h"

class PalmTree : public Tree
{
public:
	void doAction(IEntity *);
	void getAction(IEntity *);

	void Animate(std::string const &);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	Type getType() const { return PALMTREE; };
	void update(Map &);
	int getLife() const { return 0; }
};