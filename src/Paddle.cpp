#include "Paddle.h"

void Paddle::LoadTextures(std::string paddleSpritePath)
{
	if(!paddleTexture.loadFromFile(paddleSpritePath))
		std::cout << "PADDLE_CLASS: " << "Failed to load paddleTexture\n";

	paddleSprite.setTexture(paddleTexture);
}

void Paddle::InitWindowResolution()
{
	windowWidth = graphicsSettings.resolution.width;
	windowHeight = graphicsSettings.resolution.height;
}

void Paddle::InitPaddle()
{
	paddleSprite.setScale(sf::Vector2f(paddleSizeX, paddleSizeY));
	paddleSprite.setPosition(position);

	paddleSpeed = 500.f;
}

Paddle::Paddle(float startPosX, float startPosY, GraphicsSettings& graphicsSettings, std::string paddleSpritePath)
{
	this->graphicsSettings = graphicsSettings;

	position.x = startPosX;
	position.y = (startPosY / 2.f) - (paddleSizeY / 2.f);

	std::cout << position.y << "\n";

	InitWindowResolution();
	LoadTextures(paddleSpritePath);
	InitPaddle();
}

Paddle::~Paddle()
{
}

void Paddle::UpdateInput(float& deltaTime, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey)
{
	if (sf::Keyboard::isKeyPressed(UpKey))
		paddleSprite.move(sf::Vector2f(0.f, -paddleSpeed * deltaTime));

	if (sf::Keyboard::isKeyPressed(DownKey))
		paddleSprite.move(sf::Vector2f(0.f, paddleSpeed * deltaTime));
}

void Paddle::UpdateCollision(unsigned windowWidth, unsigned windowHeight)
{
	if (paddleSprite.getPosition().y < 0.f)
		paddleSprite.setPosition(paddleSprite.getPosition().x, 0.f);

	if(paddleSprite.getPosition().y + paddleSprite.getGlobalBounds().height > windowHeight)
		paddleSprite.setPosition(paddleSprite.getPosition().x, windowHeight - paddleSprite.getGlobalBounds().height);
}

void Paddle::Update(float& deltaTime)
{
	UpdateInput(deltaTime, UpKey, DownKey);
	UpdateCollision(windowWidth, windowHeight);
}

void Paddle::Render(sf::RenderWindow* window)
{
	window->draw(paddleSprite);
}

sf::Sprite Paddle::GetSprite()
{
	return paddleSprite;
}
