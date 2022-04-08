#pragma once

#include "Global.h"

class Shield
{
public:
	// Constructor & Destructor
	Shield(sf::Vector2f position);
	~Shield();

	// Functions
	void restart();
	void update(const float& dt);
	void render(sf::RenderWindow& window);

public:
	std::vector<sf::RectangleShape> shield;
	std::array<std::string, 16> sketch =
	{
		"...BBBBBBBBBB...",
		"..BBBBBBBBBBBB..",
		".BBBBBBBBBBBBBB.",
		"BBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBB",
		"BBBBB......BBBBB",
		"BBBB........BBBB",
		"BBBB........BBBB",
		"BBB..........BBB",
		"BBB..........BBB",
		"................",
		"................",
		"................",
		"................",
		"................"
	};

	sf::Vector2f defaultPos;
};

