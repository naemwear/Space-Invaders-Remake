#include "Enemy.h"

// Constructor & Destructor
Enemy::Enemy(sf::Vector2f position, unsigned short type)
{
	// Init Variables
	this->sprite.setPosition(position);
	this->type = type;
	this->sprite.scale(2.f, 2.f);
}

Enemy::~Enemy()
{
}

// Functions
void Enemy::update()
{
	// Animation
	if (this->open)
		this->open = false;
	else
		this->open = true;
}

void Enemy::shoot(const float& dt)
{
	if (this->bullets.size() <= 0)
	{
		this->shoot_chance = rand() % 2000 + 0;

		if (this->shoot_chance == 0)
		{
			sf::RectangleShape shape;
			shape.setFillColor(sf::Color::White);
			shape.setPosition(this->getCenterPosition().x, this->getCenterPosition().y + static_cast<float>(CELL_SIZE));
			shape.setSize(sf::Vector2f(4.f, 16.f));
			this->bullets.push_back(shape);
		}
	}

	for (unsigned short i = 0; i < this->bullets.size(); i++)
	{
		sf::RectangleShape& bullet = this->bullets[i];
		bullet.move(0.f, this->bullet_speed * dt);

		if (bullet.getPosition().y > static_cast<float>(WINDOW_HEIGHT + CELL_SIZE))
			this->bullets.erase(this->bullets.begin() + i);
	}
}

void Enemy::render(sf::RenderWindow& window)
{
	// Enemy
	window.draw(this->sprite);

	// Bullets
	for (sf::RectangleShape& bullet : this->bullets)
	{
		window.draw(bullet);
	}
}
