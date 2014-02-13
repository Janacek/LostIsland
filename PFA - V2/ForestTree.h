#include "Tree.h"

class ForestTree : public Tree
{
	void Animate(std::string const &);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
};