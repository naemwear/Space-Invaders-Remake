#include "PowerUp.h"

// Constructor & Destructor
PowerUp::PowerUp(sf::Texture& texture, sf::Vector2f position, unsigned short type) :
	velocity(250.f)
{
	// Init Variables
	this->sprite.setTexture(texture);
	this->texture = texture;
	this->sprite.setPosition(position);
	this->type = type;
}

PowerUp::~PowerUp()
{
}

// Functions
void PowerUp::update(const float& dt)
{
	this->sprite.move(0.f, this->velocity * dt);
}

void PowerUp::render(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}
