#pragma once

#include "Ship.h"

class Game
{
public:
	// Constructor & Destructor
	Game();
	~Game();

	// Functions
	void pollEvents();
	void check_bullet_collision(std::vector<sf::RectangleShape>& bullets);
	bool hasGameEnded();
	void restart();
	void update();
	void render();
	void run();

private:
	// Window
	sf::RenderWindow window;

	// Background
	sf::Texture texture;
	sf::Sprite background;

	// Dt
	float dt = 0.f;
	sf::Clock dtClock;

	// Ship
	Ship ship;

	// Shield
	std::array<Shield, 4> shields
	{
		Shield(sf::Vector2f(50.f, 400.f)),
		Shield(sf::Vector2f(250.f, 400.f)),
		Shield(sf::Vector2f(450.f, 400.f)),
		Shield(sf::Vector2f(650.f, 400.f))
	};

	// Enemy Manager
	EnemyManager enemyManager;

	// Points
	unsigned int points = 0;
	std::array<unsigned short, 4> point_options = { 50, 100, 150, 200 };

	// Text
	sf::Font font;
	sf::Text point_text;
	sf::Text lives_text;

	// Hearths
	sf::Texture heath_texture;
	std::vector<sf::Sprite> hearts;
	unsigned short past_lives = 0;
	bool increased = false;

	// Sounds
	sf::SoundBuffer hitBuffer;
	sf::Sound hitSound;
};

