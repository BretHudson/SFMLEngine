#include "Spritesheet.h"
#include "BEngine.h"

#include <iostream>

// Strip stuff
Strip::Strip(std::string name, int frames[], int framecount, int speed, bool loop)
{
	this->name = name;
	for (int i = 0; i < framecount; i++)
	{
		this->frames.push_back(frames[i]);
	}
	this->framecount = framecount;
	this->loop = loop;
	frame = 0;
	this->speed = speed;
	elapsed = 0;
}

void Strip::update()
{
	elapsed += BEngine::elapsed;

	while (elapsed >= (float)(speed / BEngine::framerate) / framecount)
	{
		if (frame >= framecount)
		if (loop)
			frame = 0;
		else
			frame--;
		elapsed -= (float)(speed / BEngine::framerate) / framecount;
	}
}

int Strip::getFrame()
{
	return frames[frame];
}


// Actual Spritesheet stuff
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

	rows = texture.getSize().x / width;
	columns = texture.getSize().y / height;

	curStrip = NULL;
}

void Spritesheet::add(std::string name, int frames[], int framecount, int speed)
{
	int f[sizeof(frames)];
	for (int i = 0; i < sizeof(frames); i++)
	{
		f[i] = frames[i];
	}
	Strip* strip = new Strip(name, f, framecount, speed, true);
	strips.push_back(strip);
}

void Spritesheet::add(std::string name, int frames[], int framecount, int speed, bool loop)
{
	int f[sizeof(frames)];
	for (int i = 0; i < sizeof(frames); i++)
	{
		f[i] = frames[i];
	}
	Strip* strip = new Strip(name, f, framecount, speed, loop);
	strips.push_back(strip);
	curStrip = strip;
}

void Spritesheet::play(std::string name)
{
	std::vector<Strip*>::iterator stripsIterator;

	for (stripsIterator = strips.begin(); stripsIterator != strips.end(); stripsIterator++)
	{
		if ((*stripsIterator)->name == name)
		{
			if (curStrip != NULL)
			{
				if (curStrip->name != (*stripsIterator)->name)
					(*stripsIterator)->frame = 0;
			}
			curStrip = *stripsIterator;
		}
	}
}

void Spritesheet::play(std::string name, bool reset)
{
	std::vector<Strip*>::iterator stripsIterator;

	for (stripsIterator = strips.begin(); stripsIterator != strips.end(); stripsIterator++)
	{
		if ((*stripsIterator)->name == name)
		{
			if (reset)
				(*stripsIterator)->frame = 0;
			curStrip = *stripsIterator;
		}
	}
}

void Spritesheet::update()
{
	if (curStrip != NULL)
	{
		sprite.setTextureRect(sf::IntRect(curStrip->getFrame() % rows * width, (int)(curStrip->getFrame() / rows) * height, width, height));
		curStrip->update();
	}
}

sf::Texture* Spritesheet::getTexture()
{
	return &texture;
}

sf::Sprite* Spritesheet::getSprite()
{
	return &sprite;
}
