#include "Spring.h"

#include <iostream>
#include <cstdlib>

#include "../BEngine.h"
#include "../Entity.h"

#include "../Input.h"

Spring::Spring(double x, double y) : Entity::Entity(x, y)
{
	layer = 0;
	width = 32;
	height = 32;

	type = "spring";
}

void Spring::update()
{
    Entity::update();
}

void Spring::render(sf::RenderTexture* Buffer)
{
	sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color(255, 255, 40, 255));
	rect.setPosition(this->x, this->y);
	Buffer->draw(rect);
}

