#pragma once

#include "Shield.h"

class PowerUp
{
public:
	// Constructor & Destructor
	PowerUp(sf::Texture& texture, sf::Vector2f position, unsigned short type);
	~PowerUp();

	// Getters
	const sf::Vector2f getPosition() { return this->sprite.getPosition(); }
	const sf::Vector2f getSize() { return sf::Vector2f(static_cast<float>(this->texture.getSize().x) * this->sprite.getScale().x, static_cast<float>(this->texture.getSize().y) * this->sprite.getScale().y); }
	const sf::Vector2f getCenterPosition() { return this->sprite.getPosition() + (this->getSize() / 2.f); }
	const sf::FloatRect getGlobalBounds() { return this->sprite.getGlobalBounds(); }
	const short getType() { return this->type; }

	// Functions
	void update(const float& dt);
	void render(sf::RenderWindow& window);

private:
	// Sprite
	sf::Sprite sprite;
	sf::Texture texture;
	unsigned short type;

	// Movement
	float velocity;
};

