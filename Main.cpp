#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

#include "BEngine.h"

#include "Input.h"

#include "Entities\Player.h"
#include "Entities\Solid.h"
#include "Entities\Spring.h"

int main()
{
	BEngine::init(800, 600, 60);

	World level;
	BEngine::world(&level);

	for (int i = 0; i < 15; i++)
	{
		Solid* s = new Solid(i * 32, 64);
		level.add(s);
	}

	for (int j = 0; j < 25; j++)
	{
		Solid* left = new Solid(0, 32 - j * 32);
		level.add(left);
		Solid* right = new Solid(32 * 14, 32 - j * 32);
		level.add(right);
	}

	Player player(50, 32);
	level.add(&player);
	Spring spring(50 + 32, 32);
	level.add(&spring);

	sf::Font font;
	if (!font.loadFromFile("assets/arial.ttf"))
	{
		//BEngine::error("Could not load arial.ttf");
	}

	sf::Text text;
	text.setFont(font);

	BEngine::loop();

	return 0;
}
