#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>

class IEntity
{
public:
   void doAction(IEntity* other);
   void getAction(IEntity* other);
   void Animate(std::string const & string_anim);
   int getDamage(void);
   //sf::Rect &getCollisionBox(void);

protected:
private:

};
