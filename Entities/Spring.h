#ifndef _SPRING_H_
#define _SPRING_H_

#include <SFML/Graphics.hpp>

#include "../Entity.h"

class Spring : public Entity
{
	public:
		Spring(double x, double y);

        void update();
		void render(sf::RenderTexture* Buffer);
};

#endif

