#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

#include "BEngine.h"

#include "Input.h"

#include "Entities\Player.h"
#include "Entities\Solid.h"

int main()
{
	sf::Vector2i screensize(800, 600);
	sf::Vector2i blocksize(400, 300);

	sf::RenderWindow Window;
	Window.create(sf::VideoMode(screensize.x, screensize.y), "SFML Tutorial");

	Window.setKeyRepeatEnabled(false);

	BEngine::framerate = 60;
	BEngine::camera.setSize(800, 600);
	Window.setFramerateLimit(BEngine::framerate);
	Input::init();

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

	sf::RenderTexture Buffer;
	if (!Buffer.create(800, 600))
	{
		//
	}

	while (Window.isOpen())
	{
		sf::Event Event;

		// Reset the Input
		Input::reset();

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
					Input::updatePressed(Event.key.code);
					break;
				case sf::Event::KeyReleased:
					Input::updateReleased(Event.key.code);
					break;
			}
		}

		// Update the game
		BEngine::update();
		//::itos(1000 / BEngine::elapsed / 1000)
		text.setString("FPS: " + BEngine::itos(BEngine::fps + 1) + " X: " + BEngine::itos(player.x) + " Y: " + BEngine::itos(player.y));

		// Set the center of the camera
		float cx, cy;
		cx = BEngine::camera.getCenter().x + (player.x - BEngine::camera.getCenter().x) * 3 * BEngine::elapsed;
		cy = BEngine::camera.getCenter().y + (player.y - BEngine::camera.getCenter().y) * 3 * BEngine::elapsed;
		BEngine::camera.setCenter((int)cx, (int)cy);

		// TODO: Fix camera

		/*float csx, csy;
		float sx, sy;
		csx = camera.getSize().x;
		csy = camera.getSize().y;

		sx = 800 + (200 * ((abs(player.xspeed) + abs(player.yspeed)) / player.mspeed));
		sy = 600 + (150 * ((abs(player.xspeed) + abs(player.yspeed)) / player.mspeed));

		sx = csx + ((sx - csx) * 0.1);
		sy = csy + ((sy - csy) * 0.1);

		if (sx < 400)
			sx = 400;
		if (sy < 300)
			sy = 300;

		//BEngine::camera.setSize(,);
		BEngine::camera.setSize(sx, sy);*/

		// Temp drawing
		Buffer.clear();
		Buffer.setView(BEngine::camera);
		BEngine::render(&Buffer);
		Buffer.display();

		// Render the game to the window
		Window.clear();
		Window.draw(sf::Sprite(Buffer.getTexture()));
		Window.draw(text);
		Window.display();

		// Sleep if the framerate is set
		//if (BEngine::framerate != 0) sf::sleep(sf::milliseconds(1000 / BEngine::framerate));
		//BEngine::log(BEngine::ftos((BEngine::elapsed - (1000 / BEngine::framerate))));
	}

	return 0;
}
