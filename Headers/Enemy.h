#pragma once

#include "PowerUp.h"

class Enemy
{
public:
	// Constructor & Destructor
	Enemy(sf::Vector2f position, unsigned short type);
	~Enemy();

	// Getters
	const sf::Vector2f getPosition() { return this->sprite.getPosition(); }
	const sf::Vector2f getSize() { return sf::Vector2f(static_cast<float>(this->texture.getSize().x) * this->sprite.getScale().x, static_cast<float>(this->texture.getSize().y) * this->sprite.getScale().y); }
	const sf::Vector2f getCenterPosition() { return this->sprite.getPosition() + (this->getSize() / 2.f); }
	const sf::FloatRect getGlobalBounds() { return this->sprite.getGlobalBounds(); }

	// Helper Functions
	void setTexture(sf::Texture& texture) { this->texture = texture; this->sprite.setTexture(texture); }
	void setPosition(const float positionX, const float positionY) { this->sprite.setPosition(positionX, positionY); }
	void move(const float offsetX, const float offsetY) { this->sprite.move(offsetX, offsetY); }

	// Functions
	void update();
	void shoot(const float& dt);
	void render(sf::RenderWindow& window);

private:
	// Sprite
	sf::Sprite sprite;
	sf::Texture texture;

	// Shooting
	unsigned short shoot_chance = 0;
	float bullet_speed = 400.f;

public:
	std::vector<sf::RectangleShape> bullets;
	unsigned short type = 0;
	bool open = false;
	bool dead = false;
};

