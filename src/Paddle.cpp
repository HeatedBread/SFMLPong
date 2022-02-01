#include "Paddle.h"

void Paddle::InitWindowResolution()
{
	windowWidth = graphicsSettings.resolution.width;
	windowHeight = graphicsSettings.resolution.height;
}

void Paddle::InitPaddle()
{
	paddleShape.setFillColor(sf::Color::White);
	paddleShape.setSize(sf::Vector2f(paddleSizeX, paddleSizeY));
	paddleShape.setPosition(position);

	paddleSpeed = 500.f;
}

Paddle::Paddle(float startPosX, float startPosY, GraphicsSettings& graphicsSettings)
{
	this->graphicsSettings = graphicsSettings;

	position.x = startPosX;
	position.y = (startPosY / 2.f) - (paddleSizeY / 2.f);

	std::cout << position.y << "\n";

	InitWindowResolution();
	InitPaddle();
}

Paddle::~Paddle()
{
}

void Paddle::UpdateInput(float& deltaTime, sf::Keyboard::Key UpKey, sf::Keyboard::Key DownKey)
{
	if (sf::Keyboard::isKeyPressed(UpKey))
		paddleShape.move(sf::Vector2f(0.f, -paddleSpeed * deltaTime));

	if (sf::Keyboard::isKeyPressed(DownKey))
		paddleShape.move(sf::Vector2f(0.f, paddleSpeed * deltaTime));
}

void Paddle::UpdateCollision(unsigned windowWidth, unsigned windowHeight)
{
	if (paddleShape.getPosition().y < 0.f)
		paddleShape.setPosition(paddleShape.getPosition().x, 0.f);

	if(paddleShape.getPosition().y + paddleShape.getGlobalBounds().height > windowHeight)
		paddleShape.setPosition(paddleShape.getPosition().x, windowHeight - paddleShape.getGlobalBounds().height);
}

void Paddle::Update(float& deltaTime)
{
	UpdateInput(deltaTime, UpKey, DownKey);
	UpdateCollision(windowWidth, windowHeight);
}

void Paddle::Render(sf::RenderWindow* window)
{
	window->draw(paddleShape);
}

sf::RectangleShape Paddle::GetShape()
{
	return paddleShape;
}
