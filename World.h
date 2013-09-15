#ifndef _BWORLD_H_
#define _BWORLD_H_

#include <SFML/Graphics.hpp>

#include "Entity.h"

class World
{
	public:
		World();

		bool active;
		int entityCount;

		virtual void begin();
		virtual void update();
		virtual void end();
		virtual void render(sf::RenderWindow* Window);

		void add(Entity* e);
		std::vector<Entity*> getEntities();
		void remove(Entity* e);

		bool collide(std::string type, double x, double y, int width, int height);

	private:
		std::vector<Entity*> _entityList;
		std::vector<Entity*> _renderList;
};

#endif
