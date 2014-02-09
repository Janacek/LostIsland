#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <list>
#include <string>

#include "FontManager.h"
#include "Singleton.h"

class OnScreenLogs
{
public:
	static OnScreenLogs &getInstance();

	void writeLog(std::string &);
	void update();
	void draw();

private:
	OnScreenLogs(const OnScreenLogs&) {};
	static OnScreenLogs _instance;
	OnScreenLogs();
	~OnScreenLogs();

	std::list<std::string>		_logs;
};