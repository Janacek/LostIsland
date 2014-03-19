#include "Singleton.h"
#include "GameScreen.h"
#include "StartScreen.h"
#include "SystemDefines.h"
#include "ImageManager.h"

StartScreen::~StartScreen() {
	Singleton::getInstance().isRunning = false;
}

StartScreen::StartScreen()
{

	Singleton::getInstance().isRunning = true;
	_isRunning = true;
	this->_choiceClock = new sf::Clock();
	_curPos = 0;

	_timeElapsed = sf::Time::Zero;
	_choiceClock->restart();
	_isRunning = true;
	sf::Text *e1 = new sf::Text();
	e1->setString("Play");
	sf::Text *e2 = new sf::Text();
	e2->setString("Option");
	sf::Text *e3 = new sf::Text();
	e3->setString("Exit");
	e1->setCharacterSize(30);

	e1->setFont((*FontManager::getInstance().getFont(SANSATION)));
	e2->setFont((*FontManager::getInstance().getFont(SANSATION)));
	e3->setFont((*FontManager::getInstance().getFont(SANSATION)));

	_entries.push_back(e1);
	_entries.push_back(e2);
	_entries.push_back(e3);
	
	_selector = new sf::RectangleShape(sf::Vector2f(40, 10));
	_music = new sf::Music;
	_music->openFromFile("./Media/sounds/bgm/mainTheme.ogg");

	_selection = new sf::RectangleShape(sf::Vector2f(200, 75));
	_selection->setPosition(0, 0);
	_selection->setFillColor(sf::Color(255, 255, 255, 150));
	_selection->setOutlineColor(sf::Color::White);
	_selection->setOutlineThickness(2);
}

stateName StartScreen::getStateName() const
{
	return MENU;
}

void StartScreen::events(sf::Event &)
{
}

void StartScreen::draw()
{
	Singleton::getInstance()._window->clear();

	sf::Texture *menuScreen = ImageManager::getInstance().get(MENU_SCREEN);
	sf::Sprite spriteMenu;
	spriteMenu.setTexture(*menuScreen);
	Singleton::getInstance()._window->draw(spriteMenu);

	sf::Text lostIsland;
	lostIsland.setFont(*FontManager::getInstance().getFont(SANSATION));
	lostIsland.setPosition(50, 50);
	lostIsland.setCharacterSize(60);
	lostIsland.setString("Lost Island");
	Singleton::getInstance()._window->draw(lostIsland);


	float i = 0;
	int pos = 0;
	for (std::vector<sf::Text *>::iterator it = _entries.begin(); it != _entries.end() ; ++it)
	{
		if (pos == _curPos)
		{
			_selection->setPosition(_entries[pos]->getPosition().x - 50, _entries[pos]->getPosition().y - 15);
			Singleton::getInstance()._window->draw(*_selection);
		}
		(*it)->setPosition((float)Singleton::getInstance()._window->getSize().x / 2 + 450, i + 250);
		Singleton::getInstance()._window->draw(*(*it));
		i += 75;
		++pos;
	}
	/*_selector->setPosition(_entries[_curPos]->getPosition().x - 50, _entries[_curPos]->getPosition().y + 15);
	Singleton::getInstance()._window->draw(*_selector);*/
	Singleton::getInstance()._window->display();
}

void StartScreen::initialize(void)
{
	_music->setLoop(true);
	_music->play();
}

void StartScreen::update(void)
{
	int size = _entries.size();
	sf::Time t = _choiceClock->getElapsedTime();
	float timeReload = (float)t.asMilliseconds() - _timeElapsed.asMilliseconds();
	if (Singleton::getInstance().isMovingUp == true && timeReload > 100)
	{
		_timeElapsed = _choiceClock->getElapsedTime();
		_curPos -= 1;
		if (_curPos < 0)
			_curPos = _entries.size() - 1;
	}
	else if (Singleton::getInstance().isMovingDown == true && timeReload > 100)
	{
		_timeElapsed = _choiceClock->getElapsedTime();
		
		_curPos += 1;
		if ((unsigned int)_curPos > _entries.size() - 1)
			_curPos = 0;
	}
	else if (Singleton::getInstance().isValidating == true)
	{
		if (_curPos == 0) 
		{
			_music->stop();
			_next = new GameScreen();
		}
		else if (_curPos == 1)
			_next = new OptionScreen(); // TODO
		else if (_curPos == 2)
		{
			_music->stop();
			Singleton::getInstance()._window->close();
			exit(1);
		}
		_isRunning = false;
	}
}

IScreen * StartScreen::getNextState(void)
{
	return this->_next;
}

void StartScreen::release(void)
{
}

bool StartScreen::isRunning(void) const
{
	return _isRunning;
}

