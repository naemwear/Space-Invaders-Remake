#include "EnemyManager.h"

// Constructor & Destructor
EnemyManager::EnemyManager()
{
	// Init Textures
	this->textures.loadTexture("res/enemy00.png");
	this->textures.loadTexture("res/enemy01.png");
	this->textures.loadTexture("res/enemy10.png");
	this->textures.loadTexture("res/enemy11.png");
	this->textures.loadTexture("res/enemy20.png");
	this->textures.loadTexture("res/enemy21.png");
	this->textures.loadTexture("res/ufo.png");
	this->textures.loadTexture("res/enemy-bullet.png");

	// Init Enemies
	for (unsigned short row = 1; row <= 3; row++)
	{
		for (unsigned short column = 1; column <= ((WINDOW_WIDTH - 32) / 32) / 2; column++)
		{
			this->enemies.push_back(Enemy(sf::Vector2f(32.f * column, 32.f + (32.f * row)), row - 1));
		}
	}

	this->directions = sf::Vector2i(1, 0);
	this->enemy_speed = sf::Vector2f(8.f, 32.f);
	this->moveTimer.restart();
}

EnemyManager::~EnemyManager()
{
}

// Functions
void EnemyManager::update(const float& dt)
{
	// Get the chance of spawning a UFO
	if (this->ufos.size() == 0) {
		this->ufo_spawnchance = rand() % 5500 + 0;

		if (this->ufo_spawnchance == 0)
			this->ufos.push_back(Enemy(sf::Vector2f(WINDOW_WIDTH + CELL_SIZE, 32.f), 3));
	}

	// Get the direction of the enemies
	if (this->enemies[0].getPosition().x < static_cast<float>(CELL_SIZE)) {
		this->directions.y = 1;
		this->directions.x = 1;
	}
	else if (this->enemies[this->enemies.size() - 1].getPosition().x > static_cast<float>(WINDOW_WIDTH - CELL_SIZE)) {
		this->directions.y = 1;
		this->directions.x = -1;
	}
	else
		this->directions.y = 0;

	// Enemies
	for (unsigned short i = 0; i < this->enemies.size(); i++)
	{
		Enemy& enemy = this->enemies[i];

		if (this->moveTimer.getElapsedTime().asSeconds() >= 0.65f) {
			for (Enemy& enemy : this->enemies)
			{
				enemy.update();
				enemy.move(this->enemy_speed.x * this->directions.x, this->enemy_speed.y * this->directions.y);
			}

			this->moveTimer.restart();
		}

		enemy.shoot(dt);

		if (enemy.dead)
			this->enemies.erase(this->enemies.begin() + i);
	}

	// UFOs
	for (unsigned short i = 0; i < this->ufos.size(); i++)
	{
		Enemy& enemy = this->ufos[i];
		enemy.move(-210.f * dt, 0.f);

		if (enemy.getPosition().x < static_cast<float>(-CELL_SIZE)) {
			this->ufos.erase(this->ufos.begin() + i);
		}

		if (enemy.dead)
			this->ufos.erase(this->ufos.begin() + i);
	}
}

void EnemyManager::restart()
{
	this->enemies.clear();
	this->ufos.clear();

	for (unsigned short row = 1; row <= 3; row++)
	{
		for (unsigned short column = 1; column <= ((WINDOW_WIDTH - 32) / 32) / 2; column++)
		{
			this->enemies.push_back(Enemy(sf::Vector2f(32.f * column, 32.f + (32.f * row)), row - 1));
		}
	}

	this->directions = sf::Vector2i(1, 0);
	this->enemy_speed = sf::Vector2f(8.f, 32.f);
	this->moveTimer.restart();
}

void EnemyManager::render(sf::RenderWindow& window)
{
	for (Enemy& enemy : this->enemies)
	{
		if (enemy.type == 0)
		{
			if (enemy.open)
				enemy.setTexture(this->textures.getTexture(1));
			else
				enemy.setTexture(this->textures.getTexture(0));
		}
		else if (enemy.type == 1)
		{
			if (enemy.open)
				enemy.setTexture(this->textures.getTexture(3));
			else
				enemy.setTexture(this->textures.getTexture(2));
		}
		else if (enemy.type == 2)
		{
			if (enemy.open)
				enemy.setTexture(this->textures.getTexture(5));
			else
				enemy.setTexture(this->textures.getTexture(4));
		}

		enemy.render(window);
	}

	for (Enemy& enemy : this->ufos)
	{
		enemy.setTexture(this->textures.getTexture(6));
		enemy.render(window);
	}
}
