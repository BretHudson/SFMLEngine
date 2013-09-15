#include "World.h"

#include "BEngine.h"

#include <iostream>

struct sortLayers
{
    inline bool operator() (const Entity* struct1, const Entity* struct2)
    {
		return (struct1->layer > struct2->layer);
    }
};

World::World()
{

}

void World::begin()
{
	active = false;
}

void World::update()
{
	if (active)
	{
		std::vector<Entity*>::iterator entityListIterator;

		for (entityListIterator = _entityList.begin(); entityListIterator != _entityList.end(); entityListIterator++)
		{
			(*entityListIterator)->update();
		}

		_renderList.clear();
		_renderList.reserve(_entityList.size());
		std::copy(_entityList.begin(), _entityList.end(), std::back_inserter(_renderList));
		std::stable_sort(_renderList.begin(), _renderList.end(), sortLayers());
	}
	else
	{
		active = true;
	}
}

void World::end()
{
	active = false;
}

void World::render(sf::RenderWindow* Window)
{
	std::vector<Entity*>::iterator renderListIterator;

	for (renderListIterator = _renderList.begin(); renderListIterator != _renderList.end(); renderListIterator++)
	{
		Entity* e = (*renderListIterator);
		e->render(Window);
	}
}

void World::add(Entity* e)
{
	e->added();
	_entityList.push_back((Entity*)e);
	entityCount++;
}

std::vector<Entity*> World::getEntities()
{
	return _renderList;
}

void World::remove(Entity* e)
{
	e->removed();
	_entityList.erase(std::remove(_entityList.begin(), _entityList.end(), e), _entityList.end());
	entityCount--;
}


bool World::collide(std::string type, double x, double y, int width, int height)
{
	std::vector<Entity*>::iterator entitiesIterator;

	int i = 0;

	// Make sure this entity has a hitbox set up
	if ((width >= 0) && (height >= 0))
	{
		for (entitiesIterator = _entityList.begin(); entitiesIterator != _entityList.end(); entitiesIterator++)
		{
			i++;
			Entity* e = (*entitiesIterator);
			if (e->type == type)
			{
				// Make sure the other entity has a hitbox set up
				if ((width >= 0) && (height >= 0))
				{
					int x2 = e->x;
					int y2 = e->y;
					int width2 = e->width;
					int height2 = e->height;

					if ((x < x2 + width2) && (x + width > x2) && (y < y2 + height2) && (y + height > y2))
					{
						return true;
					}
				}
				//else if (mask != NULL)
			}
		}
	}

	return false;
}
