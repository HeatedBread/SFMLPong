#pragma once
#include <iostream>
#include <fstream>

#include "GraphicsSettings.h"

class Paddle
{
private:
	sf::Vector2f position;
	sf::RectangleShape paddleShape;

	sf::Sprite paddleSprite;
	sf::Texture paddleTexture;

	float paddleSizeX = 5.f, paddleSizeY = 5.f;
	float paddleSpeed;

	GraphicsSettings graphicsSettings;
	unsigned windowWidth, windowHeight;

public:
	sf::Keyboard::Key UpKey;
	sf::Keyboard::Key DownKey;

private:
	void LoadTextures(std::string paddleSpritePath);

	void InitWindowResolution();
	void InitPaddle();

public:

	Paddle(float startPosX, float startPosY, GraphicsSettings& graphicsSettings, std::string paddleSpritePath);
	virtual ~Paddle();

	void UpdateInput(float& deltaTime, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);
	void UpdateCollision(unsigned windowWidth, unsigned windowHeight);

	void Update(float& deltaTime);
	void Render(sf::RenderWindow* window);

	sf::Sprite GetSprite();
};
