#pragma once

#include "EnemyManager.h"

class Ship
{
public:
	// Constructor & Destructor
	Ship();
	~Ship();

	// Getters
	const sf::Vector2f getPosition() { return this->sprite.getPosition(); }
	const sf::Vector2f getSize() { return sf::Vector2f(static_cast<float>(this->texture.getSize().x) * this->sprite.getScale().x, static_cast<float>(this->texture.getSize().y) * this->sprite.getScale().y); }
	const sf::Vector2f getCenterPosition() { return this->sprite.getPosition() + (this->getSize() / 2.f); }
	const sf::FloatRect getGlobalBounds() { return this->sprite.getGlobalBounds(); }

	// Functions
	int enemy_collision(std::vector<Enemy>& enemies, std::vector<Enemy>& ufos);
	int powerUp_check();
	void restart();
	void update(const float& dt);
	void render(sf::RenderWindow& window);

private:
	// Sprite
	sf::Sprite sprite;
	sf::Texture texture;

	// Movement
	float velocity;


	// Sounds
	sf::SoundBuffer shootBuffer;
	sf::Sound shootSound;

public:
	// Health
	unsigned short lives = 3;
	bool dead = false;

	// Shooting
	sf::Clock reload_timer;
	std::vector<sf::RectangleShape> bullets;
	float reload_time = 1.17f;
	float bullet_speed = 450.f;
	unsigned short bullets_fired = 0;

	// Power Up
	std::vector<PowerUp> powerUps;
	TextureManager powerUp_textures;
	sf::Clock powerUp_timer;
	float powerUp_time = 10.f;
};

