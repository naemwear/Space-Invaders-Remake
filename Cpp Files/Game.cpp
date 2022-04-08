#include "Game.h"

// Constructor & Destructor
Game::Game() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Invaders Remake", sf::Style::Close | sf::Style::Titlebar)
{
	// Init Window
	this->window.setVerticalSyncEnabled(VSYNC);
	if (FRAME_LIMIT > 0)
		this->window.setFramerateLimit(FRAME_LIMIT);

	// Background
	this->texture.loadFromFile("res/background.png");
	this->background.setTexture(this->texture);

	// Init UI
	this->font.loadFromFile("res/font/AncientModernTales-a7Po.ttf");

	this->point_text.setFont(this->font);
	this->point_text.setCharacterSize(24);
	this->point_text.setStyle(sf::Text::Bold);

	this->lives_text.setFont(this->font);
	this->lives_text.setCharacterSize(24);
	this->lives_text.setStyle(sf::Text::Bold);
	this->lives_text.setPosition(2.f, static_cast<float>(WINDOW_HEIGHT - CELL_SIZE));
	this->lives_text.setString("Lives: ");
	this->past_lives = this->ship.lives;

	this->heath_texture.loadFromFile("res/heart.png");

	for (unsigned short i = 1; i <= this->ship.lives; i++)
	{
		sf::Sprite sprite;
		sprite.setTexture(this->heath_texture);
		sprite.setPosition(32.f + (32.f * i), static_cast<float>(WINDOW_HEIGHT - CELL_SIZE));
		this->hearts.push_back(sprite);
	}
	
	// Init Sounds
	this->hitBuffer.loadFromFile("res/hit.wav");
	this->hitSound.setBuffer(this->hitBuffer);
}

Game::~Game()
{
}

// Functions
void Game::pollEvents()
{
	sf::Event events;
	while (this->window.pollEvent(events))
	{
		switch (events.type)
		{
		case sf::Event::Closed:
			this->window.close();
			break;
		}
	}
}

void Game::check_bullet_collision(std::vector<sf::RectangleShape>& bullets)
{
	for (unsigned short i = 0; i < bullets.size(); i++)
	{
		sf::RectangleShape& bullet = bullets[i];

		for (unsigned short j = 0; j < this->shields.size(); j++)
		{
			Shield& shield = this->shields[j];

			for (unsigned short b = 0; b < shield.shield.size(); b++)
			{
				sf::RectangleShape& part = shield.shield[b];

				if (bullet.getGlobalBounds().intersects(part.getGlobalBounds()))
				{
					shield.shield.erase(shield.shield.begin() + b);
					bullets.erase(bullets.begin() + i);
					break;
				}
			}
		}
	}
}

bool Game::hasGameEnded()
{
	

	if (this->ship.dead)
		return true;
	else if (this->enemyManager.enemies.size() <= 0)
		return true;
	else if (this->enemyManager.enemies[this->enemyManager.enemies.size() - 1].getPosition().y >= 400.f)
		return true;

	return false;
}

void Game::restart()
{
	// Restart shields
	for (Shield& shield : this->shields)
	{
		shield.restart();
	}

	// Reset Player
	this->ship.restart();

	// Reset the enemies
	this->enemyManager.restart();

	// Reset the hearts
	this->hearts.clear();
	for (unsigned short i = 1; i <= this->ship.lives; i++)
	{
		sf::Sprite sprite;
		sprite.setTexture(this->heath_texture);
		sprite.setPosition(32.f + (32.f * i), static_cast<float>(WINDOW_HEIGHT - CELL_SIZE));
		this->hearts.push_back(sprite);
	}

	this->past_lives = this->ship.lives;

	this->points = 0;
}

void Game::update()
{
	// Check if game has ended
	if (this->hasGameEnded()) {
		this->restart();
		return;
	}

	// UI
	this->point_text.setString("Points: " + std::to_string(this->points));

	// Enemies
	this->enemyManager.update(this->dt);

	// Ship Reset stuff
	if (this->ship.powerUp_timer.getElapsedTime().asSeconds() >= this->ship.powerUp_time)
	{
		if (this->ship.reload_time != 1.17f)
			this->ship.reload_time = 1.17f;

		if (this->enemyManager.enemy_speed.x != 8.f)
			this->enemyManager.enemy_speed.x = 8.f;
	}

	// Player Collision
	if (!this->ship.dead)
	{

		for (auto& enemy : this->enemyManager.enemies)
		{
			if (enemy.bullets.size() > 0)
			{
				for (unsigned short i = 0; i < enemy.bullets.size(); i++)
				{
					sf::RectangleShape& bullet = enemy.bullets[i];

					if (this->ship.getGlobalBounds().intersects(bullet.getGlobalBounds()))
					{
						this->ship.lives--;
						enemy.bullets.erase(enemy.bullets.begin() + i);
					}
				}
			}
		}

		// Ship
		int collision_number = this->ship.enemy_collision(this->enemyManager.enemies, this->enemyManager.ufos);
		int powerUp_number = this->ship.powerUp_check();
		this->ship.update(this->dt);

			// Check Collision
		if (collision_number == 1)
			this->points += 10;
		else if (collision_number == -1)
			this->points += this->point_options[rand() % 4 + 0];

			// Check for PowerUps
		if (powerUp_number == 1)
			this->ship.reload_time /= 2.f;
		else if (powerUp_number == 2)
			this->enemyManager.enemy_speed.x /= 2.f;
		else if (powerUp_number == 3)
			this->ship.lives += 1;

		// Check for new hearts
		if (this->hearts.size() > 0)
		{
			if (this->ship.lives != this->past_lives)
			{
				short differnece = this->ship.lives - this->past_lives;

				if (differnece > 0)
				{
					for (int i = 1; i <= differnece; i++)
					{
						sf::Sprite sprite;
						sprite.setTexture(this->heath_texture);
						sprite.setPosition(this->hearts[this->hearts.size() - 1].getPosition().x + static_cast<float>(CELL_SIZE), static_cast<float>(WINDOW_HEIGHT - CELL_SIZE));

						this->hearts.push_back(sprite);
					}
				}
				else
				{
					for (int i = 0; i < -differnece; i++)
					{
						this->hearts.pop_back();
					}
				}
			}
		}

		this->past_lives = this->ship.lives;
	}
	else
	{
		if (!this->ship.bullets.empty())
			this->ship.bullets.clear();
	}

	// Shields
	for (Enemy& enemy : this->enemyManager.enemies)
	{
		if (enemy.bullets.size() > 0)
			this->check_bullet_collision(enemy.bullets);
	}

	if (this->ship.bullets.size() > 0)
		this->check_bullet_collision(this->ship.bullets);

	for (Shield& shield : this->shields)
	{
		shield.update(dt);
	}

	if (this->ship.lives <= 0) {
		this->ship.dead = true;
		this->hitSound.play();
	}
}

void Game::render()
{
	// Clear the screen
	this->window.clear();

	// Background
	this->window.draw(this->background);

	// Enemies
	this->enemyManager.render(this->window);

	// Shields
	for (Shield& shield : this->shields)
	{
		shield.render(this->window);
	}

	// Ship
	this->ship.render(this->window);

	// UI
	this->window.draw(this->point_text);
	this->window.draw(this->lives_text);

	for (sf::Sprite& heart : this->hearts)
	{
		this->window.draw(heart);
	}

	// Display
	this->window.display();
}

void Game::run()
{
	while (this->window.isOpen())
	{
		this->dt = this->dtClock.restart().asSeconds();
		this->pollEvents();
		this->update();
		this->render();
	}
}
