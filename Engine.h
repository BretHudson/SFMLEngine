#ifndef _BH_ENGINE_H_
#define _BH_ENGINE_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Engine
{
	public:
		Engine();
		void log(sf::String s);
		void update();
		void render(sf::RenderWindow* Window);
	private:

};

#endif
