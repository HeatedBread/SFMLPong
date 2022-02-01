#pragma once

#include "Paddle.h"

class Ball
{
private:
	sf::Vector2f position;
	sf::RectangleShape ballShape;

	sf::Vector2f ballSize = sf::Vector2f(25.f, 25.f);
	sf::Vector2f ballSpeed = sf::Vector2f(150.f, 100.f);
	float ballSpeedMultiplier = 1.15f;

	GraphicsSettings graphicsSettings;
	unsigned windowWidth, windowHeight;

private:
	void InitWindowResolution();
	void InitBall();

public:
	Ball(float startPosX, float startPosY, GraphicsSettings& graphicsSettings);
	virtual ~Ball();

	void UpdateCollision(unsigned windowWidth, unsigned windowHeight);
	void UpdateMovement(float deltaTime);
	
	void Update(float& deltaTime);
	void Render(sf::RenderWindow* window);

	void SwapDirectionX();
	void SwapDirectionY();

	sf::RectangleShape GetShape();
};
