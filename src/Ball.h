#pragma once

#include "Paddle.h"

class Ball
{
private:
	sf::Vector2f position;
	sf::RectangleShape ballShape;

	sf::Sprite ballSprite;
	sf::Texture ballTexture;

	sf::Vector2f ballSize = sf::Vector2f(2.3f, 2.3f);

	sf::Vector2f ballVelocity;
	float ballSpeed;
	const float ballInitialSpeed = 180.f;
	float ballSpeedMultiplier = 1.15f;

	GraphicsSettings graphicsSettings;
	unsigned windowWidth, windowHeight;
	float resizeScale;

private:
	void LoadTextures();

	void InitWindowResolution();
	void InitBall();

public:
	Ball(float startPosX, float startPosY, GraphicsSettings& graphicsSettings);
	virtual ~Ball();

	void UpdateCollision();
	void UpdateMovement(float deltaTime);
	
	void Update(float& deltaTime);
	void Render(sf::RenderWindow* window);

	void SwapDirectionX();
	void SwapDirectionY();

	void StartGame();
	void Reset();

	sf::Sprite GetSprite();
};
