#include "Tree.h"
#include "ShadersManager.h"
#include "Animation.h"
#include "AnimatedSprite.h"

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
	Type getType() const;
	virtual void loadAnimation(std::string const & string_anim, float speed);


private:
	Animation							*_waveAnim;
	Animation							*_curAnim;
	AnimatedSprite						*_animatedSprite;

	sf::Clock							_mvtClock;
	double								_oldDtMvt;
	double								_oldTime;
};