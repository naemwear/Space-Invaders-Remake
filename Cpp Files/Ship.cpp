#include "Ship.h"

// Constructor & Destructor
Ship::Ship() :
	velocity(200.f)
{
	// Init Variables
	this->sprite.setPosition(static_cast<float>(WINDOW_WIDTH / 2), static_cast<float>(WINDOW_HEIGHT - CELL_SIZE * 2));
	this->texture.loadFromFile("res/ship.png");
	this->sprite.setTexture(this->texture);
	this->sprite.scale(2.f, 2.f);
	this->reload_timer.restart();

	// Init Textures
	this->powerUp_textures.loadTexture("res/double_bullets.png");
	this->powerUp_textures.loadTexture("res/half_speed.png");
	this->powerUp_textures.loadTexture("res/extra_health.png");

	// Init Sounds
	this->shootBuffer.loadFromFile("res/shoot.wav");
	this->shootSound.setBuffer(this->shootBuffer);
}

Ship::~Ship()
{
}

// Functions
float min(float a, float b)
{
	if (a < b)
		return a;
	else
		return b;
}

float max(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}

int Ship::enemy_collision(std::vector<Enemy>& enemies, std::vector<Enemy>& ufos)
{
	if (this->bullets.size() > 0)
	{
		for (unsigned int b = 0; b < this->bullets.size(); b++)
		{
			sf::RectangleShape& bullet = this->bullets[b];

			sf::Vector2f thisHitBox = bullet.getSize();
			sf::Vector2f thisPosition = bullet.getPosition() + (thisHitBox / 2.f);

			for (Enemy& enemy : enemies)
			{
				sf::Vector2f otherHitBox = sf::Vector2f(enemy.getSize().x / 2.f - 11.f, enemy.getSize().y / 2.f - 11.f);
				sf::Vector2f otherPosition = enemy.getCenterPosition();

				float deltaX = otherPosition.x - thisPosition.x;
				float deltaY = otherPosition.y - thisPosition.y;
				float intersectX = abs(deltaX) - (otherHitBox.x + thisHitBox.x);
				float intersectY = abs(deltaY) - (otherHitBox.y + thisHitBox.y);

				if (intersectX < 0.f && intersectY < 0.f)
				{
					this->bullets.erase(this->bullets.begin() + b);
					enemy.dead = true;

					return 1;
				}
			}

			for (Enemy& ufo : ufos)
			{
				if (ufo.getGlobalBounds().intersects(bullet.getGlobalBounds()))
				{
					this->bullets.erase(this->bullets.begin() + b);
					ufo.dead = true;

					int type = (rand() % 3 + 1) - 1;
					this->powerUps.push_back(PowerUp(this->powerUp_textures.getTexture(type),
						sf::Vector2f(ufo.getCenterPosition().x, ufo.getCenterPosition().y + CELL_SIZE), type));

					return -1;
				}
			}
		}
	}

	return 0;
}

int Ship::powerUp_check()
{
	for (unsigned short i = 0; i < this->powerUps.size(); i++)
	{
		PowerUp& powerUp = this->powerUps[i];

		if (this->sprite.getGlobalBounds().intersects(powerUp.getGlobalBounds()))
		{
			this->powerUp_timer.restart();
			int type = powerUp.getType();
			this->powerUps.erase(this->powerUps.begin() + i);

			return type + 1;
		}
	}

	return 0;
}

void Ship::restart()
{
	this->dead = false;
	this->lives = 3;
	this->sprite.setPosition(static_cast<float>(WINDOW_WIDTH / 2), static_cast<float>(WINDOW_HEIGHT - CELL_SIZE * 2));
	this->texture.loadFromFile("res/ship.png");
	this->sprite.setTexture(this->texture);
	this->reload_timer.restart();
	this->bullets.clear();
	this->powerUps.clear();
	this->reload_time = 1.17f;
	this->bullets_fired = 0;
}

void Ship::update(const float& dt)
{
	// Movement
	float x = this->sprite.getPosition().x;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		x = max(this->sprite.getPosition().x + -this->velocity * dt, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		x = min(this->sprite.getPosition().x + this->velocity * dt, static_cast<float>(WINDOW_WIDTH - CELL_SIZE));

	this->sprite.setPosition(x, this->sprite.getPosition().y);

	// Shooting
		// Spawning Bullets
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->reload_timer.getElapsedTime().asSeconds() >= this->reload_time || this->bullets_fired <= 0) {
			sf::RectangleShape shape;
			shape.setPosition(sf::Vector2f(this->getCenterPosition().x - 4.f, this->sprite.getPosition().y - static_cast<float>(CELL_SIZE + 8)));
			shape.setSize(sf::Vector2f(4.f, 16.f));
			shape.setFillColor(sf::Color::Green);
			this->bullets.push_back(shape);
			this->bullets_fired++;
			this->reload_timer.restart();
			this->shootSound.play();
		}
	}

		// Bullets
	if (this->bullets.size() > 0)
	{
		for (unsigned short i = 0; i < this->bullets.size(); i++)
		{
			sf::RectangleShape& bullet = this->bullets[i];
			bullet.move(0.f, -this->bullet_speed * dt);

			if (bullet.getPosition().y + static_cast<float>(CELL_SIZE) < 0.f)
				this->bullets.erase(this->bullets.begin() + i);
		}
	}

	// PowerUps
	for (unsigned short i = 0; i < this->powerUps.size(); i++)
	{
		// Update
		PowerUp& powerUp = this->powerUps[i];
		powerUp.update(dt);

		// Erase if bellow the screen
		if (powerUp.getPosition().y > static_cast<float>(WINDOW_HEIGHT))
			this->powerUps.erase(this->powerUps.begin() + i);
	}
}

void Ship::render(sf::RenderWindow& window)
{
	// Bullets
	if (this->bullets.size() > 0)
	{
		for (sf::RectangleShape& bullet : this->bullets)
		{
			window.draw(bullet);
		}
	}

	// PowerUps
	for (PowerUp& powerUp : this->powerUps)
	{
		powerUp.render(window);
	}

	// Sprite
	if (this->dead)
		this->texture.loadFromFile("res/dead_ship.png");
	window.draw(this->sprite);
}
