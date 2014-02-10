#include "OnScreenLogs.h"

OnScreenLogs OnScreenLogs::_instance = OnScreenLogs();

OnScreenLogs &OnScreenLogs::getInstance()
{
	return _instance;
}

OnScreenLogs::OnScreenLogs()
{
}

void OnScreenLogs::writeLog(std::string &log)
{
	_logs.push_back(log);
	if (_logs.size() > 20)
		_logs.pop_front();
}

OnScreenLogs::~OnScreenLogs()
{
}

void OnScreenLogs::update()
{
}

void OnScreenLogs::draw()
{
	int x = 0;

	for (auto it = _logs.begin(); it != _logs.end(); ++it)
	{
		sf::Text tmp;

		tmp.setFont(*FontManager::getInstance().getFont(SANSATION));
		tmp.setString(*it);
		tmp.setPosition(10, x);
		Singleton::getInstance()._window->draw(tmp);
		x += 15;
	}
}