#include "GameOverScreen.h"
#include "Singleton.h"

GameOverScreen::GameOverScreen()
{
	_isRunning = true;
	_currentPosition = 0;

	_gameOverScreen = new sf::Image;
	_gameOverScreen->loadFromFile("./Media/images/gameOverScreen.png");
}

void GameOverScreen::events(sf::Event &)
{

}

void GameOverScreen::initialize()
{

}

void GameOverScreen::draw()
{
	Singleton::getInstance()._window->clear();

	sf::Texture gameOverScreen;
	gameOverScreen.loadFromImage(*_gameOverScreen);
	sf::Sprite spriteGameOver;
	spriteGameOver.setTexture(gameOverScreen);
	Singleton::getInstance()._window->draw(spriteGameOver);

	sf::Text gameOver;
	gameOver.setFont(*FontManager::getInstance().getFont(SANSATION));
	gameOver.setPosition((1920 / 2) - (gameOver.getGlobalBounds().width / 2), 200);
	gameOver.setCharacterSize(60);
	gameOver.setString("Game Over...");
	Singleton::getInstance()._window->draw(gameOver);

	sf::Text pressKey;
	pressKey.setFont(*FontManager::getInstance().getFont(SANSATION));
	pressKey.setPosition((1920 / 2) - (gameOver.getGlobalBounds().width / 2), 400);
	pressKey.setCharacterSize(60);
	pressKey.setString("Press Escape key to exit");
	Singleton::getInstance()._window->draw(pressKey);

	Singleton::getInstance()._window->display();

}

void GameOverScreen::update()
{
	if (Singleton::getInstance().isEscapePressed == true)
	if (sf::Keyboard::isKeyPressed)
	{
		_next = new StartScreen;
		_isRunning = false;
	}
}

stateName GameOverScreen::getStateName() const
{
	return GAMEOVER;
}

IScreen *GameOverScreen::getNextState()
{
	return _next;
}

void GameOverScreen::release()
{

}

bool GameOverScreen::isRunning() const
{
	return _isRunning;
}

GameOverScreen::~GameOverScreen()
{

}