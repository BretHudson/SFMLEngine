#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

#include "BEngine.h"

#include "Entities\Player.h"

// Tutorial 18

int main()
{
	sf::Vector2i screensize(800, 600);
	sf::Vector2i blocksize(400, 300);

	sf::RenderWindow Window;
	Window.create(sf::VideoMode(screensize.x, screensize.y), "SFML Tutorial");

	Window.setKeyRepeatEnabled(false);

	BEngine::framerate = 45;

	World level;
	BEngine::world(&level);

	Entity w(0, 32);
	w.width = 32;
	w.height = 32;
	w.type = "solid";
	level.add(&w);

	Entity q(800-32, 32);
	q.width = 32;
	q.height = 32;
	q.type = "solid";
	level.add(&q);

	Entity wall(0, 64);
	wall.width = 800;
	wall.height = 32;
	wall.type = "solid";
	level.add(&wall);

	Player p(50, 32);
	level.add(&p);

	srand(time(0));

	sf::View camera(sf::FloatRect(0, 0, 800, 600));
	Window.setView(camera);

	sf::Font font;
	if (!font.loadFromFile("assets/arial.ttf"))
	{
		//BEngine::error("Could not load arial.ttf");
	}

	sf::Text text;
	text.setFont(font);

	sf::RenderTexture buffer;
	if (!buffer.create(800, 600))
	{
		//
	}

	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			switch (Event.type)
			{
				case sf::Event::Closed:
					Window.close();
					break;
				case sf::Event::KeyPressed:
					if (Event.key.code == sf::Keyboard::Escape)
						Window.close();
					break;
			}
		}

		// Sleep if the framerate is set
		if (BEngine::framerate != 0) sf::sleep(sf::milliseconds(1000 / BEngine::framerate));

		// Update the game
		BEngine::update();

		text.setString("FPS: " + BEngine::itos(1000 / BEngine::elapsed / 1000) + " Y: " + BEngine::ftos(p.y));

		// Temp drawing
		buffer.clear();
		buffer.setView(BEngine::camera);
		buffer.display();

		// Render the game to the window
		Window.clear();
		BEngine::render(&buffer);
		Window.draw(sf::Sprite(buffer.getTexture()));
		Window.draw(text);
		Window.display();
	}

	Window.close();
	return 0;
}
