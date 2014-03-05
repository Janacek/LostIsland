#include "Tree.h"
#include "ShadersManager.h"
#include "Animation.h"
#include "AnimatedSprite.h"

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
	virtual void loadAnimation(std::string const & string_anim, float speed);
	void update(Map &);

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);

private:
	Animation							*_waveAnim;
	Animation							*_curAnim;
	AnimatedSprite						*_animatedSprite;

	sf::Clock							_mvtClock;
	double								_oldDtMvt;
	double								_oldTime;
};