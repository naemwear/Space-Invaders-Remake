#pragma once

#include "Enemy.h"

class EnemyManager
{
public:
	// Constructor & Destructor
	EnemyManager();
	~EnemyManager();

	// Functions
	void update(const float& dt);
	void restart();
	void render(sf::RenderWindow& window);

public:
	std::vector<Enemy> enemies;
	std::vector<Enemy> ufos;
	sf::Vector2f enemy_speed;

private:
	TextureManager textures;
	sf::Clock moveTimer;
	sf::Vector2i directions;
	unsigned short ufo_spawnchance = 0;
};

