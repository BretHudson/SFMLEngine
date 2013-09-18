#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>

#include "../Entity.h"
#include "../Spritesheet.h"

class Player : public Entity
{
	public:
		Player(double x, double y);

		void update();
		void render(sf::RenderTexture* Buffer);

		enum State {
			STANDING,
			WALKING,
			RUNNING,
			TURNAROUND,
			SLOWDOWN,
			FRICTION,
			JUMPING,
			FALLING,
			SLIDING
		};

		std::vector<std::string> StateName;

		sf::Texture texture;
		sf::Sprite sprite;
		Spritesheet* spritesheet;

	public:
		// Move functions
		void input();
		void inputx();
		void inputy();
		void accelerate(int dir);
		void modSpeeds();
		void movePlayer();
		void moveX();
		void moveY();

		State state;

		float xspeed;
		float yspeed;

		float aspeed;
		float fspeed;
		float mspeed;
		float rspeed;

		float gspeed;
		float jspeed;
		float sjspeed;
		float wjspeed;

		float wallTimer;
		float wallTimerLimit;
};

#endif

