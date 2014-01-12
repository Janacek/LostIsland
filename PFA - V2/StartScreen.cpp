#include "Singleton.h"
#include "GameScreen.h"
#include "StartScreen.h"

StartScreen::StartScreen()
{
	_isRunning = true;
	this->_choiceClock = new sf::Clock();
	_curPos = 0;
}

stateName StartScreen::getStateName() const
{
	return MENU;
}


void StartScreen::draw()
{
	Singleton::getInstance()._window->clear();
	float i = 0;
	for (std::vector<sf::Text *>::iterator it = _entries.begin(); it != _entries.end() ; ++it)
	{
		(*it)->setPosition((float)Singleton::getInstance()._window->getSize().x / 2, i);
		Singleton::getInstance()._window->draw(*(*it));
		i += 50;
	}
	_selector->setPosition(_entries[_curPos]->getPosition().x - 50, _entries[_curPos]->getPosition().y + 15);
	Singleton::getInstance()._window->draw(*_selector);
	Singleton::getInstance()._window->display();
}

void StartScreen::initialize(void)
{
	_timeElapsed = sf::Time::Zero;
	_choiceClock->restart();
	_isRunning = true;
	sf::Text *e1 = new sf::Text();
	e1->setString("Play");
	sf::Text *e2 = new sf::Text();
	e2->setString("Option");
	sf::Text *e3 = new sf::Text();
	e3->setString("Exit");
	//	sf::Text *e4 = new sf::Text();
	//e4->setString("Local Game");
	//sf::Text *e5 = new sf::Text();
	//e5->setString("Local Game");
	_font.loadFromFile("./Media/Sansation.ttf");
	e1->setCharacterSize(30);
	e1->setFont(_font);
	e2->setFont(_font);
	e3->setFont(_font);

	_entries.push_back(e1);
	_entries.push_back(e2);
	_entries.push_back(e3);
	
	_selector = new sf::RectangleShape(sf::Vector2f(40, 10));
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
			_next = new GameScreen();
		}
		if (_curPos == 1)
			_next = NULL; // TODO
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

