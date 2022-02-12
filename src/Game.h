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

	Ball* ball;
	Paddle* playerOne;
	Paddle* playerTwo;

	sf::Font font;
	sf::Text playerOneScoreText, playerTwoScoreText;

	int playerOneScore, playerTwoScore;

private:
	void InitVariables();
	void InitGraphicsSettings();
	void InitKeys();
	void InitWindow();
	void InitObjects();

	void InitScore(int scoreCharSize, sf::Color scoreColour, float yOffset);

public: 
	Game();
	virtual ~Game();

	void UpdateObjects(float deltaTime);
	void UpdateCollisions();
	void UpdateScore();
	void Update();
	void UpdateEvents();
	
	void RenderUI();
	void RenderObjects();
	void Render();
	void Run();
};
