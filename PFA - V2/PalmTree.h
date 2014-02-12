#include "Tree.h"

class PalmTree : public Tree
{
public:
	void Animate(std::string const &);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
};