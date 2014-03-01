#include "Tree.h"
#include "ShadersManager.h"

class PalmTree : public Tree
{
public:
	PalmTree();
	void doAction(AEntity *);
	void getAction(AEntity *);

	void Animate(std::string const &);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	Type getType() const { return PALMTREE; };
	void update(Map &);
};