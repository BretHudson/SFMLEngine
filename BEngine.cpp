#include "BEngine.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

namespace BEngine
{
	World* _world = NULL;

	sf::Clock _deltaClock;
	sf::Time _deltaTime;
	int framerate = 0;
	int fps = 0;
	int framesThisSecond;
	float elapsed;
	float elapsedThisSecond = 0;

	sf::RenderWindow Window;
	sf::Vector2i screensize;
	sf::RenderTexture Buffer;

	sf::View camera;

	void log(sf::String s)
	{
        std::cout << "BEngine: " << s.toAnsiString() << std::endl;
	}

	void error(sf::String s)
	{
		std::cout << "Error: " << s.toAnsiString() << std::endl;
	}

	void init(int width, int height)
	{
        init(width, height, 60);
	}

	void init(int width, int height, int frate)
	{
        Window.create(sf::VideoMode(width, height), "Engine Window");
        camera.setSize(width, height);
        screensize.x = width;
        screensize.y = height;
        framerate = frate;
        Window.setFramerateLimit(BEngine::framerate);
        Input::init();
        srand(time(0));
        Window.setKeyRepeatEnabled(false);
        camera.setViewport(sf::FloatRect(0, 0, width, height));
        Window.setView(camera);

        if (!Buffer.create(width, height))
        {
            //
        }
	}

	void loop()
	{
	    sf::Font font;
        if (!font.loadFromFile("assets/arial.ttf"))
        {
            //BEngine::error("Could not load arial.ttf");
        }

        sf::Text text;
        text.setFont(font);

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
                    case sf::Event::JoystickButtonPressed:
                        Input::updateJoystickPressed(Event.joystickButton.joystickId, Event.joystickButton.button);
                        break;
                    case sf::Event::JoystickButtonReleased:
                        Input::updateJoystickReleased(Event.joystickButton.joystickId, Event.joystickButton.button);
                        break;
                }
            }

            // Update the game
            update();
            //::itos(1000 / BEngine::elapsed / 1000)
            text.setString("FPS: " + BEngine::itos(BEngine::fps + 1));

            // Set the center of the camera
            /*float cx, cy;
            cx = BEngine::camera.getCenter().x + (player.x - BEngine::camera.getCenter().x) * 3 * BEngine::elapsed;
            cy = BEngine::camera.getCenter().y + (player.y - BEngine::camera.getCenter().y) * 3 * BEngine::elapsed;
            BEngine::camera.setCenter((int)cx, (int)cy);*/

            // Temp drawing
            Buffer.clear();
            Buffer.setView(camera);
            render(&Buffer);
            Buffer.display();

            // Render the game to the window
            Window.clear();
            Window.draw(sf::Sprite(Buffer.getTexture()));
            Window.draw(text);
            Window.display();

            log("Blah!");

            // Sleep if the framerate is set
            //if (BEngine::framerate != 0) sf::sleep(sf::milliseconds(1000 / BEngine::framerate));
            //BEngine::log(BEngine::ftos((BEngine::elapsed - (1000 / BEngine::framerate))));
        }
	}

	void update()
	{
	    Window.display();
		_deltaTime = _deltaClock.restart();
		elapsed = _deltaTime.asSeconds();
		elapsedThisSecond += elapsed;

		framesThisSecond++;
		if (elapsedThisSecond > 1.0f)
		{
			fps = framesThisSecond;
			elapsedThisSecond -= 1.0f;
			framesThisSecond = 0;
		}

		if (_world)
			_world->update();
	}

	void render(sf::RenderTexture* Buffer)
	{
		if (_world)
			_world->render(Buffer);
	}

	World* world()
	{
		return _world;
	}

	void world(World* w)
	{
		_world = w;
	}

	int sign(float n)
	{
		return (0 < n) - (n < 0);
	}

	std::string itos(int n)
	{
	   std::stringstream ss;//create a stringstream
	   ss << n;//add number to the stream
	   return ss.str();//return a string with the contents of the stream
	}

	std::string ftos(float n)
	{
	   std::stringstream ss;//create a stringstream
	   ss << n;//add number to the stream
	   return ss.str();//return a string with the contents of the stream
	}
}
