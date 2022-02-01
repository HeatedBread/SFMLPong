#include "Ball.h"

void Ball::InitWindowResolution()
{
	windowWidth = graphicsSettings.resolution.width;
	windowHeight = graphicsSettings.resolution.height;
}

void Ball::InitBall()
{
	ballShape.setFillColor(sf::Color::White);
	ballShape = sf::RectangleShape(ballSize);
	ballShape.setPosition(position);
}

Ball::Ball(float startPosX, float startPosY, GraphicsSettings& graphicsSettings)
{
	this->graphicsSettings = graphicsSettings;

	// Set the Y position to a random range
	position.x = startPosX - ballSize.x;
	position.y = startPosY - ballSize.y;

	InitWindowResolution();
	InitBall();
}

Ball::~Ball()
{
}

void Ball::UpdateCollision(unsigned windowWidth, unsigned windowHeight)
{
	if (ballShape.getPosition().y < 0.f)
		SwapDirectionY();

	if (ballShape.getPosition().y + ballShape.getGlobalBounds().height > windowHeight)
		SwapDirectionY();
}

void Ball::UpdateMovement(float deltaTime)
{
	ballShape.move(ballSpeed * deltaTime);
}

void Ball::Update(float& deltaTime)
{
	UpdateMovement(deltaTime);
	UpdateCollision(windowWidth, windowHeight);
}

void Ball::Render(sf::RenderWindow* window)
{
	window->draw(ballShape);
}

void Ball::SwapDirectionX()
{
	ballSpeed.x = -ballSpeed.x * ballSpeedMultiplier;
}

void Ball::SwapDirectionY()
{
	ballSpeed.y = -ballSpeed.y * ballSpeedMultiplier;
}

sf::RectangleShape Ball::GetShape()
{
	return ballShape;
}
