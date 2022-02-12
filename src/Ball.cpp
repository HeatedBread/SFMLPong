#include "Ball.h"

void Ball::LoadTextures()
{
	if (!ballTexture.loadFromFile("assets/art/pong_ball.png"))
		std::cout << "BALL_CLASS: " << "Failed to load ballTexture\n";

	ballSprite.setTexture(ballTexture);
}

void Ball::InitWindowResolution()
{
	windowWidth = graphicsSettings.resolution.width;
	windowHeight = graphicsSettings.resolution.height;
}

void Ball::InitBall()
{
	ballSprite.setScale(ballSize);
	ballSprite.setPosition(position);

	ballSpeed = ballInitialSpeed;
	ballVelocity = sf::Vector2f(0.0f, 0.0f);
}

Ball::Ball(float startPosX, float startPosY, GraphicsSettings& graphicsSettings)
{
	srand(time(NULL));

	this->graphicsSettings = graphicsSettings;

	position.x = startPosX - ballSize.x;
	position.y = startPosY - ballSize.y;

	InitWindowResolution();
	LoadTextures();
	InitBall();
	StartGame();
}

Ball::~Ball()
{
}

void Ball::UpdateCollision()
{
	// Floor and Ceiling collision
	if (ballSprite.getPosition().y < 0.f)
		SwapDirectionY();
	if (ballSprite.getPosition().y + ballSprite.getGlobalBounds().height > windowHeight)
		SwapDirectionY();
}

void Ball::UpdateMovement(float deltaTime)
{
	ballSprite.move(ballVelocity * deltaTime);
}	

void Ball::Update(float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		StartGame();

	UpdateMovement(deltaTime);
	UpdateCollision();
}

void Ball::Render(sf::RenderWindow* window)
{
	window->draw(ballSprite);
}

void Ball::SwapDirectionX()
{
	ballVelocity.x = -ballVelocity.x * ballSpeedMultiplier;
}

void Ball::SwapDirectionY()
{
	ballVelocity.y = -ballVelocity.y * ballSpeedMultiplier;
}

void Ball::StartGame()
{
	ballVelocity.y = ((rand() % 2) == 0) ? ballSpeed : -ballSpeed;
	ballVelocity.x = ((rand() & 2) == 0) ? ballSpeed : -ballSpeed;
}

void Ball::Reset()
{
	ballSprite.setPosition(windowWidth / 2.f - ballSize.x, windowHeight / 2.f - ballSize.y);
	ballVelocity = sf::Vector2f(0.f, 0.f);
	ballSpeed = ballInitialSpeed;
	StartGame();
}

sf::Sprite Ball::GetSprite()
{
	return ballSprite;
}
