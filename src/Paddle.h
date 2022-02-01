#pragma once
#include <iostream>
#include <fstream>

#include "GraphicsSettings.h"

class Paddle
{
private:
	sf::Vector2f position;
	sf::RectangleShape paddleShape;

	float paddleSizeX = 45.f, paddleSizeY = 175.f;
	float paddleSpeed;

	GraphicsSettings graphicsSettings;
	unsigned windowWidth, windowHeight;

public:
	sf::Keyboard::Key UpKey;
	sf::Keyboard::Key DownKey;

private:
	void InitWindowResolution();
	void InitPaddle();

public:

	Paddle(float startPosX, float startPosY, GraphicsSettings& graphicsSettings);
	virtual ~Paddle();

	void UpdateInput(float& deltaTime, sf::Keyboard::Key UpKey, sf::Keyboard::Key DownKey);
	void UpdateCollision(unsigned windowWidth, unsigned windowHeight);

	void Update(float& deltaTime);
	void Render(sf::RenderWindow* window);

	sf::RectangleShape GetShape();
};
