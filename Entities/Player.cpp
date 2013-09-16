#include "Player.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "../BEngine.h"
#include "../Entity.h"

Player::Player(double x, double y) : Entity::Entity(x, y)
{
	layer = -1;
	width = 32;
	height = 32;

	xspeed = 0.0f;
	yspeed = 0.0f;

	// Horizontal speeds
	aspeed = 1150.0f;
	fspeed = 1550.0f;
	mspeed = 620.0f;
	rspeed = 930.0f;

	// Vertical speeds
	jspeed = 700.0f;
	sjspeed = 800.0f;
	wjspeed = 950.0f;
	gspeed = 1850.0f;

	wallTimer = 0;
	wallTimerLimit = 0.125;

	state = STANDING;

	type = "player";

	StateName.push_back("standing");
	StateName.push_back("walking");
	StateName.push_back("running");
	StateName.push_back("turning around");
	StateName.push_back("slowing down");
	StateName.push_back("friction");
	StateName.push_back("jumping");
	StateName.push_back("falling");
	StateName.push_back("sliding");

	Input::define("fuck", sf::Keyboard::C, sf::Keyboard::Z, sf::Keyboard::G);
}

void Player::update()
{
	if (yspeed != 0)
		state = STANDING;
	else
		state = (yspeed > 0) ? FALLING : JUMPING;

	input();
	modSpeeds();
	movePlayer();

	//BEngine::log("State: " + StateName[state]);
}

void Player::render(sf::RenderTexture* Buffer)
{
	sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color(255, 127 + x, 9 + y, 255));
	//rect.setFillColor(sf::Color(255, 127, 9, 255));
	rect.setPosition(this->x, this->y);
	Buffer->draw(rect);
}

void Player::input()
{
	inputx();
	inputy();
}

void Player::inputx()
{
	int dir = Input::check(sf::Keyboard::Right) - Input::check(sf::Keyboard::Left);

	if (!Input::check(sf::Keyboard::LShift))
		accelerate(1 * dir);
	else
		accelerate(2 * dir);

	if ((!Input::check(sf::Keyboard::Left)) && (!Input::check(sf::Keyboard::Right)) && (abs(xspeed) > 0))
	{
		if (collide("solid", x, y + 1))
		{
			state = FRICTION;

			if (abs(xspeed) > fspeed * BEngine::elapsed)
				xspeed -= fspeed * BEngine::sign(xspeed) * BEngine::elapsed;
			else
				xspeed = 0;
		}
		else
		{
			if (abs(xspeed) > fspeed * BEngine::elapsed / 4)
				xspeed -= fspeed * BEngine::sign(xspeed) * BEngine::elapsed / 4;
			else
				xspeed = 0;
		}
	}
}

void Player::inputy()
{
	if (Input::pressed(sf::Keyboard::Up))
	{
		if (!collide("solid", x, y + 1))
		{
			wallTimer = wallTimerLimit;
			if (collide("solid", x - 1, y))
			{
				state = JUMPING;
				xspeed = mspeed;
				yspeed = -wjspeed;
			}
			else if (collide("solid", x + 1, y))
			{
				state = JUMPING;
				xspeed = -mspeed;
				yspeed = -wjspeed;
			}
		}
		else
		{
			if (state == TURNAROUND)
			{
				BEngine::log("FRICTION JUMP");
				state = JUMPING;
				// TODO: Fix the xspeed stuff
				xspeed = 0;
				yspeed = -sjspeed;
			}
			else
			{
				state = JUMPING;
				yspeed = -jspeed;
			}
		}
	}

	if ((!Input::check(sf::Keyboard::Up)) && (yspeed < 0))
	{
		yspeed += gspeed * BEngine::elapsed;
	}
}

void Player::accelerate(int dir)
{
	state = (Input::check(sf::Keyboard::LShift)) ? RUNNING : WALKING;

	if (BEngine::sign(xspeed) == BEngine::sign(dir))
	{
		xspeed += aspeed * dir * BEngine::elapsed;
	}
	else
	{
		state = TURNAROUND;
		xspeed += fspeed * dir * BEngine::elapsed;
	}
}

void Player::modSpeeds()
{
	if (!Input::check(sf::Keyboard::LShift))
	{
		if (abs(xspeed) > mspeed)
		{
			xspeed -= fspeed * BEngine::sign(xspeed) * BEngine::elapsed * 2;
			if (abs(xspeed) < mspeed)
				xspeed = (mspeed * BEngine::sign(xspeed));
		}
	}
	else
	{
		if (abs(xspeed) > rspeed)
			xspeed = (rspeed * BEngine::sign(xspeed));
	}

	yspeed += gspeed * BEngine::elapsed;
}

void Player::movePlayer()
{
	moveX();
	moveY();
}

void Player::moveX()
{
	xspeed *= BEngine::elapsed;

	if (((collide("solid", x - 1, y)) || (collide("solid", x + 1, y))) && (wallTimer > wallTimerLimit))
		wallTimer = 0;
	else
		wallTimer += BEngine::elapsed;

	for (int i = 0; i < abs((int)xspeed); i++)
	{
		if (!collide("solid", x + BEngine::sign(xspeed), y))
		{
			if ((collide("solid", x - BEngine::sign(xspeed), y)) && (!collide("solid", x, y + 1))) // On wall
			{
				if (wallTimer >= wallTimerLimit)
				{
					x += BEngine::sign(xspeed);
				}
			}
			else
				x += BEngine::sign(xspeed);
		}
		else
		{
			xspeed = 0;
			break;
		}
	}

	if (!collide("solid", x + (xspeed - (int)xspeed), y))
	{
		x += (xspeed - (int)xspeed);
		if (collide("solid", x + 1, y)) x = ceil(x);
		if (collide("solid", x - 1, y)) x = floor(x);
	}
	else
	{
		xspeed = 0;
	}

	xspeed /= BEngine::elapsed;
}

void Player::moveY()
{
	yspeed *= BEngine::elapsed;

	for (int j = 0; j < abs((int)yspeed); j++)
	{
		if (!collide("solid", x, y + BEngine::sign(yspeed)))
		{
			y += BEngine::sign(yspeed);
		}
		else
		{
			yspeed = 0;
			break;
		}
	}

	if (!collide("solid", x, y + (yspeed - (int)yspeed)))
	{
		y += (yspeed - (int)yspeed);
		if (collide("solid", x, y + 1)) y = ceil(y);
		if (collide("solid", x, y - 1)) y = floor(y);
	}
	else
	{
		yspeed = 0;
	}

	yspeed /= BEngine::elapsed;

	if ((state == FALLING) || (state == JUMPING))
	{
		//
	}
}
