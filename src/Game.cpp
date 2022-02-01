#include "Game.h"

void Game::InitVariables()
{
	this->window = NULL;
	this->deltaTime = 0.f;
}

void Game::InitGraphicsSettings()
{
	graphicsSettings.LoadFromFile("Config/config.ini");
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
		graphicsSettings
	);

	this->playerTwo = new Paddle(
		this->window->getSize().x - 95.f,
		float(this->window->getSize().y),
		graphicsSettings
	);

	this->ball = new Ball(
		(this->graphicsSettings.resolution.width / 2.f),
		(this->graphicsSettings.resolution.height / 2.f),
		graphicsSettings
	);
}

void Game::InitFont()
{
	if (!font.LoadFromFile("assets/fonts/PixelFont.ttf"))
	{
		std::cout << "FONT ERROR: " << "Cannot find PixelFont.ttf" << "\n";
		return;
	}

	scoreBoard.setFont(font);
	scoreBoard.setCharacterSize(13);
	scoreBoard.setFillColor(sf::Color::White);
	scoreBoard.setPosition(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
	scoreBoard.setString("TEST");
}

Game::Game()
{
	InitVariables();
	InitGraphicsSettings();
	InitWindow();
	InitObjects();
	InitKeys();
	InitFont();
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
	if (ball->GetShape().getGlobalBounds().intersects(playerOne->GetShape().getGlobalBounds()))
		ball->SwapDirectionX();

	if (ball->GetShape().getGlobalBounds().intersects(playerTwo->GetShape().getGlobalBounds()))
		ball->SwapDirectionX();
}

void Game::Update()
{
	UpdateEvents();
	UpdateObjects(this->deltaTime);
	UpdateCollisions();
}

void Game::RenderObjects()
{
	this->playerOne->Render(this->window);
	this->playerTwo->Render(this->window);

	this->ball->Render(this->window);
}


void Game::Render()
{
	this->window->clear();

	RenderObjects();

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
