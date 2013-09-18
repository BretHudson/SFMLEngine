#ifndef _BENTITY_H_
#define _BENTITY_H_

#include <SFML/Graphics.hpp>

class Entity
{
	public:
		Entity();
		Entity(double x, double y);
		Entity(double x, double y, sf::Sprite* graphic);

		virtual void added();
		virtual void update();
		virtual void removed();
		virtual void render(sf::RenderTexture* Buffer);

		bool collide(std::string type, double x, double y);

		double x, y;
		int width, height;
		int layer;
		std::string type;

		sf::Sprite* graphic;

	private:
		//
};

#endif
