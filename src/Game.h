#pragma once

#include <stdlib.h>

#include "Paddle.h"
#include "Ball.h"

class Game
{
private:
	std::string title = "Pong";

	sf::RenderWindow* window;
	sf::Event event;

	sf::Clock clock;
	float deltaTime = 0.f;

	GraphicsSettings graphicsSettings;

	Paddle* playerOne;
	Paddle* playerTwo;
	Ball* ball;

	sf::Font font;
	sf::Text scoreBoard;

private:
	void InitVariables();
	void InitGraphicsSettings();
	void InitKeys();
	void InitWindow();
	void InitObjects();

	void InitFont();

public: 
	Game();
	virtual ~Game();

	void UpdateObjects(float deltaTime);
	void UpdateCollisions();
	void Update();
	void UpdateEvents();
	
	void RenderObjects();
	void Render();
	void Run();
};
