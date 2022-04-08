#include "Shield.h"

// Constructor & Destructor
Shield::Shield(sf::Vector2f position)
{
	this->defaultPos = position;

	for (unsigned short y = 0; y < 16; y++)
	{
		for (unsigned short x = 0; x < 16; x++)
		{
			char cell = this->sketch[y][x];

			if (cell != '.')
			{
				if (cell == 'B')
				{
					sf::RectangleShape sprite;
					sprite.setFillColor(sf::Color(0, 152, 0));
					sprite.setSize(sf::Vector2f(4.f, 4.f));
					sprite.setPosition(position.x + (4.f * x), position.y + (4.f * y));
					this->shield.push_back(sprite);
				}
			}
		}
	}
}

Shield::~Shield()
{
}

// Functions
void Shield::restart()
{
	this->shield.clear();

	for (unsigned short y = 0; y < 16; y++)
	{
		for (unsigned short x = 0; x < 16; x++)
		{
			char cell = this->sketch[y][x];

			if (cell != '.')
			{
				if (cell == 'B')
				{
					sf::RectangleShape sprite;
					sprite.setFillColor(sf::Color(0, 152, 0));
					sprite.setSize(sf::Vector2f(4.f, 4.f));
					sprite.setPosition(this->defaultPos.x + (4.f * x), this->defaultPos.y + (4.f * y));
					this->shield.push_back(sprite);
				}
			}
		}
	}
}

void Shield::update(const float& dt)
{
}

void Shield::render(sf::RenderWindow& window)
{
	for (sf::RectangleShape& shape : this->shield)
	{
		window.draw(shape);
	}
}
