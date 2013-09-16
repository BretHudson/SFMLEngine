#ifndef _SOLID_H_
#define _SOLID_H_

#include <SFML/Graphics.hpp>

#include "../Entity.h"

class Solid : public Entity
{
	public:
		Solid(double x, double y);

		void render(sf::RenderTexture* Buffer);
};

#endif

