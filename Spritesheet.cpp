#include "Spritesheet.h"
#include "BEngine.h"

#include <iostream>

Spritesheet::Spritesheet(std::string file, int width, int height)
{
	if (texture.loadFromFile(file))
	{
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	}
	else
		BEngine::log("Spritesheet failed to initialize - texture undefined");

	this->width = width;
	this->height = height;

	frame = 0;

	rows = texture.getSize().x / width;
	columns = texture.getSize().y / height;

	BEngine::log("Rows: " + BEngine::itos(rows) + " Columns: " + BEngine::itos(columns));
}

void Spritesheet::add(std::string name, int frames[])
{
	//
}

void Spritesheet::update()
{
	if (frame >= rows * columns)
		frame = 0;

	sprite.setTextureRect(sf::IntRect(frame % rows * width, (int)(frame / rows) * height, width, height));

	frame++;
}

sf::Texture* Spritesheet::getTexture()
{
	return &texture;
}

sf::Sprite* Spritesheet::getSprite()
{
	return &sprite;
}
