#include "Tree.h"
#include "ShadersManager.h"

class Bush : public Tree
{
public:
	void				Animate(std::string const &);
	void				draw(sf::RenderTexture *, sf::Shader &);
	void				draw(sf::RenderTexture *);
};