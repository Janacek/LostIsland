#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>

class Singleton
{
public:
   void getInstance(void);

protected:
private:
   sf::RenderWindow _window;
   sf::Clock _clock;
   bool isLeftClicking;
   bool isRightClicking;
   sf::Vector2f posLeftClick;
   sf::Vector2f posRightClick;
   bool isValidating;
   sf::Clock _animClock;


};