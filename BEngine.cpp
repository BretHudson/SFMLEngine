#include "BEngine.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

/*void BEngine::log(sf::String s)
{
	std::cout << "BEngine: " << s.toAnsiString() << std::endl;
}

void BEngine::update()
{
	if (world())
		world()->update();
}

void BEngine::render(sf::RenderWindow* Window)
{
	if (world())
		world()->render(Window);
}

World* BEngine::world()
{
	return BEngine::_world;
}

void BEngine::world(World* w)
{
	BEngine::_world = w;
}*/

namespace BEngine
{
	World* _world = NULL;

	sf::Clock _deltaClock;
	sf::Time _deltaTime;
	extern int framerate = 0;
	float elapsed;

	sf::View camera;

	void log(sf::String s)
	{
		std::cout << "BEngine: " << s.toAnsiString() << std::endl;
	}

	void error(sf::String s)
	{
		std::cout << "Error: " << s.toAnsiString() << std::endl;
	}

	void update()
	{
		_deltaTime = _deltaClock.restart();
		elapsed = _deltaTime.asSeconds();

		if (_world)
			_world->update();
	}

	void render(sf::RenderWindow* Window)
	{
		if (_world)
			_world->render(Window);
		Window->setView(camera);
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
