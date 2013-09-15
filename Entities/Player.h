#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>

#include "../Entity.h"

class Player : public Entity
{
	public:
		Player(double x, double y);

		void update();
		void render(sf::RenderWindow* Window);

		// Move functions
		void input();
		void accelerate(int dir);
		void modSpeeds();
		void movePlayer();
		void moveX();
		void moveY();

	private:
		float xspeed;
		float yspeed;
		float aspeed;
		float fspeed;
		float mspeed;
		float rspeed;
		float gspeed;
		float jspeed;
		bool running;
};

#endif

