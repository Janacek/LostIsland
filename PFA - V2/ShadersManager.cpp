#include "ShadersManager.h"

ShadersManager ShadersManager::m_instance = ShadersManager();

ShadersManager::ShadersManager()
{
	start();
}

void ShadersManager::start()
{
	sf::Shader *flag;
	flag = new sf::Shader();
	flag->loadFromFile("./shaders/selectedShader.vert", "./shaders/selectedShader.frag");
	_mapShaders[FLAG] = flag;

	sf::Shader *bloom;
	bloom = new sf::Shader();
	bloom->loadFromFile("./shaders/glowShader.vert", "./shaders/glowShader.frag");
	_mapShaders[BLOOM] = bloom;
}

sf::Shader *ShadersManager::get(ShaderType id)
{
	return _mapShaders[id];
}

ShadersManager &ShadersManager::getInstance()
{
	return m_instance;
}

ShadersManager::~ShadersManager()
{

}