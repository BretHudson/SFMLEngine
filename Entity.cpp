#include "Entity.h"
#include "BEngine.h"

#include <iostream>

Entity::Entity()
{
	x = 0;
	y = 0;
	graphic = NULL;
	width = 0;
	height = 0;
	layer = 0;
	this->type = "none";
}

Entity::Entity(double x, double y)
{
	this->x = x;
	this->y = y;
	graphic = NULL;
	width = 0;
	height = 0;
	layer = 0;
	this->type = "none";
}

Entity::Entity(double x, double y, sf::Sprite* graphic)
{
	this->x = x;
	this->y = y;
	this->graphic = graphic;
	width = 0;
	height = 0;
	layer = 0;
	this->type = "none";
}

void Entity::added()
{
	//
}

void Entity::update()
{
	//
}

void Entity::removed()
{
	//
}

void Entity::render(sf::RenderTexture* Buffer)
{
	if (graphic != NULL)
	{
		graphic->setPosition(x, y);
		Buffer->draw(*graphic);
	}
}

bool Entity::collide(std::string type, double x, double y)
{
	int width = this->width;
	int height = this->height;

	return BEngine::world()->collide(type, x, y, width, height);
}
