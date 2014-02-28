#include "Tree.h"
#include "ShadersManager.h"

class Map;

class ForestTree : public Tree
{
public:
	ForestTree();
	void doAction(AEntity *);
	void getAction(AEntity *);

	void Animate(std::string const &);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	void update(Map &);
	Type getType() const { return TREE; };
};