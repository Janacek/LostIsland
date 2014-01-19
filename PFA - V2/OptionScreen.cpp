#include "OptionScreen.h"

OptionScreen::OptionScreen()
{
	_isRunning = true;

	_button = sfg::Button::Create("Hello");
	_window = sfg::Window::Create();

	_button->GetSignal(sfg::Button::OnLeftClick).Connect(
		std::bind(&OptionScreen::onButtonClick, this)
		);

	_window->SetTitle("Hello World example");
	_window->Add(_button);
	_desktop.Add(_window);
}

void OptionScreen::events(sf::Event &e)
{
	_window->HandleEvent(e);
}

void OptionScreen::initialize()
{
}

void OptionScreen::onButtonClick() {
	_button->SetLabel("World");
}

void OptionScreen::draw()
{
	Singleton::getInstance()._window->clear();

	Singleton::getInstance()._sfgui.Display(*Singleton::getInstance()._window);

	Singleton::getInstance()._window->display();
}

void OptionScreen::update()
{
	if (Singleton::getInstance().isEscapePressed)
	{
		_isRunning = false;
		_next = new StartScreen();
	}

	_desktop.Update(Singleton::getInstance()._clock->restart().asSeconds());
}

stateName OptionScreen::getStateName() const
{
	return OPTIONS;
}

IScreen *OptionScreen::getNextState()
{
	return this->_next;
}

void OptionScreen::release()
{

}

bool OptionScreen::isRunning() const
{
	return this->_isRunning;
}