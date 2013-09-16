#include "Solid.h"

#include <iostream>
#include <cstdlib>

#include "../BEngine.h"
#include "../Entity.h"

#include "../Input.h"

Solid::Solid(double x, double y) : Entity::Entity(x, y)
{
	layer = 0;
	width = 32;
	height = 32;

	type = "solid";
}

void Solid::render(sf::RenderTexture* Buffer)
{
	sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color(255, 40, 255, 255));
	rect.setPosition(this->x, this->y);
	Buffer->draw(rect);
}
