#pragma once

#include <fstream>

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

class GraphicsSettings
{
public:
	std::string title;
	sf::VideoMode resolution;
	bool fullScreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;

public:
	GraphicsSettings();

	void SaveFromFile(const std::string path);
	void LoadFromFile(const std::string path);
};
