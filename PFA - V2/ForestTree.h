#include "Tree.h"
#include "ShadersManager.h"

class Map;

class ForestTree : public Tree
{
	void doAction(IEntity *);
	void getAction(IEntity *);

	void Animate(std::string const &);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	void update(Map &);
	Type getType() const { return TREE; };
};