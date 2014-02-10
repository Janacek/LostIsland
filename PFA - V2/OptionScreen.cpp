#include "OptionScreen.h"

void OptionScreen::musicAdjustmentChange(void)
{
	std::cout << "music : " << _musicAdjustment->GetValue() << std::endl;
}

void OptionScreen::sfxAdjustmentChange(void)
{
	std::cout << "sfx : " << _sfxAdjustment->GetValue() << std::endl;
}

OptionScreen::OptionScreen()
{
	_isRunning = true;

	_window = sfg::Window::Create();
	_window->SetStyle(sfg::Window::NO_STYLE);

	
	_musicScale = sfg::Scale::Create(sfg::Scale::Orientation::HORIZONTAL);
	_musicLabel = sfg::Label::Create("Musics : ");
	_musicAdjustment = _musicScale->GetAdjustment();
	_musicAdjustment->SetLower(0);
	_musicAdjustment->SetUpper(100);
	_musicAdjustment->SetMinorStep(3.f);
	_musicAdjustment->SetMajorStep(12.f);
	_musicAdjustment->SetPageSize(0.f);
	_musicAdjustment->GetSignal(sfg::Adjustment::OnChange).Connect(
		std::bind(&OptionScreen::musicAdjustmentChange, this));
	_musicScale->SetRequisition(sf::Vector2f(100, 20));
	_musicAdjustment->SetValue(50);
	auto musicBox = sfg::Box::Create();
	musicBox->Pack(_musicLabel);
	musicBox->Pack(_musicScale);

	_sfxScale = sfg::Scale::Create(sfg::Scale::Orientation::HORIZONTAL);
	_sfxLabel = sfg::Label::Create("sfxs : ");
	_sfxAdjustment = _sfxScale->GetAdjustment();
	_sfxAdjustment->SetLower(0);
	_sfxAdjustment->SetUpper(100);
	_sfxAdjustment->SetMinorStep(3.f);
	_sfxAdjustment->SetMajorStep(12.f);
	_sfxAdjustment->SetPageSize(0.f);
	_sfxAdjustment->GetSignal(sfg::Adjustment::OnChange).Connect(
		std::bind(&OptionScreen::sfxAdjustmentChange, this));
	_sfxScale->SetRequisition(sf::Vector2f(100, 20));
	_sfxAdjustment->SetValue(50);
	auto sfxBox = sfg::Box::Create();
	sfxBox->Pack(_sfxLabel);
	sfxBox->Pack(_sfxScale);


	auto table = sfg::Table::Create();

	table->Attach(musicBox, sf::Rect<sf::Uint32>(0, 0, 1, 1));
	table->Attach(sfxBox, sf::Rect<sf::Uint32>(0, 1, 1, 1));

	_window->Add(table);
	_desktop.Add(_window);
}

void OptionScreen::events(sf::Event &e)
{
	_window->HandleEvent(e);
}

void OptionScreen::initialize()
{
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

OptionScreen::~OptionScreen() {

}