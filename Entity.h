#ifndef _BENTITY_H_
#define _BENTITY_H_

#include <SFML/Graphics.hpp>

class Entity
{
	public:
		Entity();
		Entity(double x, double y);

		virtual void added();
		virtual void update();
		virtual void removed();
		virtual void render(sf::RenderWindow* Window);

		bool collide(std::string type, double x, double y);

		double x, y;
		int width, height;
		int layer;
		std::string type;

	private:
		//
};

#endif
