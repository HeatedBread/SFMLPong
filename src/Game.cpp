#include "Game.h"

void Game::InitVariables()
{
	this->window = NULL;
	this->deltaTime = 0.f;
}

void Game::InitGraphicsSettings()
{
	graphicsSettings.loadFromFile("config/config.ini");
}

void Game::InitKeys()
{
	playerOne->UpKey = sf::Keyboard::W;
	playerOne->DownKey = sf::Keyboard::S;
	playerTwo->UpKey = sf::Keyboard::Up;
	playerTwo->DownKey = sf::Keyboard::Down;

}

void Game::InitWindow()
{
	if (this->graphicsSettings.fullScreen)
	{
		this->window = new sf::RenderWindow(
			this->graphicsSettings.resolution,
			this->graphicsSettings.title,
			sf::Style::Fullscreen,
			this->graphicsSettings.contextSettings
		);
	}
	else {
		this->window = new sf::RenderWindow(
			this->graphicsSettings.resolution,
			this->graphicsSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->graphicsSettings.contextSettings
		);
	}

	this->window->setFramerateLimit(graphicsSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(graphicsSettings.verticalSync);
}

void Game::InitObjects()
{
	this->playerOne = new Paddle(
		50.f,
		float(this->window->getSize().y),
		graphicsSettings,
		"assets/art/paddle_sprite_left.png"
	);

	this->playerTwo = new Paddle(
		this->window->getSize().x - 95.f,
		float(this->window->getSize().y),
		graphicsSettings,
		"assets/art/paddle_sprite_left.png"
	);

	this->ball = new Ball(
		(this->graphicsSettings.resolution.width / 2.f),
		(this->graphicsSettings.resolution.height / 2.f),
		graphicsSettings
	);
}

void Game::InitScore(int scoreCharSize, sf::Color scoreColour, float yOffset)
{
	font.loadFromFile("assets/fonts/PixelFont.ttf");

	int xOffset = this->window->getSize().x / 2.f;

	playerOneScoreText.setFont(font);
	playerOneScoreText.setString("99");
	playerOneScoreText.setCharacterSize(scoreCharSize);
	playerOneScoreText.setFillColor(scoreColour);
	playerOneScoreText.setPosition(xOffset / 2.f, yOffset);

	playerTwoScoreText.setFont(font);
	playerTwoScoreText.setString("99");
	playerTwoScoreText.setCharacterSize(25);
	playerTwoScoreText.setFillColor(scoreColour);
	playerTwoScoreText.setPosition(xOffset * 1.5f, yOffset);
}

Game::Game()
{
	InitVariables();
	InitGraphicsSettings();
	InitWindow();
	InitObjects();
	InitKeys();
	InitScore(25, sf::Color::White, 50.f);
}

Game::~Game()
{
	delete this->window;
}

void Game::UpdateEvents()
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::UpdateObjects(float deltaTime)
{
	playerOne->Update(deltaTime);
	playerTwo->Update(deltaTime);

	ball->Update(deltaTime);
}

void Game::UpdateCollisions()
{
	if (ball->GetSprite().getGlobalBounds().intersects(playerOne->GetSprite().getGlobalBounds()))
		ball->SwapDirectionX();

	if (ball->GetSprite().getGlobalBounds().intersects(playerTwo->GetSprite().getGlobalBounds()))
		ball->SwapDirectionX();
}

void Game::UpdateScore()
{
	// Player 2 Scored
	if (this->ball->GetSprite().getPosition().x < 0.0f)
	{
		playerTwoScore++;
		this->ball->Reset();
	}

	// Player 1 Scored
	if (this->ball->GetSprite().getPosition().x > this->window->getSize().x)
	{
		playerOneScore++;
		this->ball->Reset();
	}

	///
	/// RETURN TO THIS TO FIGURE OUT HOW TO SCALE ALL OBJECTS IN PROJECT
	///

	playerOneScoreText.setString(std::to_string(playerOneScore));
	playerTwoScoreText.setString(std::to_string(playerTwoScore));
}

void Game::Update()
{
	UpdateEvents();
	UpdateObjects(this->deltaTime);
	UpdateCollisions();
	UpdateScore();
}

void Game::RenderUI()
{
	this->window->draw(this->playerOneScoreText);
	this->window->draw(this->playerTwoScoreText);
}

void Game::RenderObjects()
{
	this->playerOne->Render(this->window);
	this->playerTwo->Render(this->window);

	this->ball->Render(this->window);
}


void Game::Render()
{
	this->window->clear(sf::Color(30, 10, 53, 255));

	RenderObjects();
	RenderUI();

	this->window->display();
}

void Game::Run()
{
	while (this->window->isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		this->Update();
		this->Render();
	}
}
