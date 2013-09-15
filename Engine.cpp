#include "Engine.h"

Engine::Engine()
{
	std::cout << "BEngine: Engine started" << std::endl;
}

void Engine::log(sf::String s)
{
	//std::cout << "BEngine: " << s.toAnsiString() << std::endl;
}

void Engine::update()
{
	//this->log("Update");
}

void Engine::render(sf::RenderWindow* Window)
{
	/*Window->display();
	Window->clear();*/
}
