#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iterator>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 576;
constexpr int CELL_SIZE = 32;
constexpr unsigned short FRAME_LIMIT = 0;
constexpr bool VSYNC = false;

class TextureManager
{
public:
	TextureManager() {}
	~TextureManager() {}

	// Functions
	void loadTexture(std::string path)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(path))
			return;

		this->textures.push_back(texture);
	}

	sf::Texture& getTexture(unsigned int index)
	{
		if (index >= this->textures.size())
			std::cout << "TextureManager.cpp::getTexture: Invalid index " << index << "\n";
		else
			return this->textures[index];
	}

private:
	std::vector<sf::Texture> textures;
};