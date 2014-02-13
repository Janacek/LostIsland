#pragma once

#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>

#include <map>

enum ShaderType
{
	FLAG= 0,
	BLOOM,
	WAVE,
};

class ShadersManager
{
public:
	static ShadersManager& getInstance();

	void start();
	sf::Shader *get(ShaderType id);
private:
	ShadersManager(const ShadersManager&) {};
	static ShadersManager m_instance;
	ShadersManager();
	~ShadersManager();
	std::map<ShaderType, sf::Shader *> _mapShaders;
};