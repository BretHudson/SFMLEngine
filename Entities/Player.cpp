#include "Player.h"

#include <iostream>
#include <cstdlib>

#include "../BEngine.h"
#include "../Entity.h"

Player::Player(double x, double y) : Entity::Entity(x, y)
{
	layer = -1;
	width = 32;
	height = 32;

	xspeed = 0.0f;
	yspeed = 0.0f;
	aspeed = 1250.0f;
	fspeed = 1550.0f;
	mspeed = 620.0f;
	rspeed = 850.0f;
	jspeed = 700.0f;
	gspeed = 1850.0f;

	state = STANDING;

	type = "player";
}

void Player::update()
{
	state = STANDING;

	input();
	modSpeeds();
	movePlayer();

	// Set camera stuff
	float cx, cy;
	cx = BEngine::camera.getCenter().x + (x - BEngine::camera.getCenter().x) * 3 * BEngine::elapsed;
	cy = BEngine::camera.getCenter().y + (y - BEngine::camera.getCenter().y) * 3 * BEngine::elapsed;

	//BEngine::camera.setSize(800 + (200 * ((abs(xspeed) + abs(yspeed)) / mspeed)), 600 + (150 * ((abs(xspeed) + abs(yspeed)) / mspeed)));
	BEngine::camera.setSize(800, 600);

	BEngine::camera.setCenter(cx, cy);
	//BEngine::camera.rotate(30 * BEngine::elapsed);

	BEngine::log("State: " + BEngine::itos(state));
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
	running = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!running)
			accelerate(-1);
		else
			accelerate(-2);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (!running)
			accelerate(1);
		else
			accelerate(2);
	}

	if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	{
		if (abs(xspeed) > fspeed * BEngine::elapsed)
			xspeed -= fspeed * BEngine::sign(xspeed) * BEngine::elapsed;
		else
			xspeed = 0;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (collide("solid", x, y + 1)))
	{
		yspeed = -jspeed;
	}

	if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (yspeed < 0))
	{
		yspeed += gspeed * BEngine::elapsed;
	}
}

void Player::accelerate(int dir)
{
	if (BEngine::sign(xspeed) == BEngine::sign(dir))
	{
		state = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? RUNNING : WALKING;
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
	if (!running)
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

	for (int i = 0; i < abs((int)xspeed); i++)
	{
		if (!collide("solid", x + BEngine::sign(xspeed), y))
			x += BEngine::sign(xspeed);
		else
		{
			xspeed = 0;
			break;
		}
	}

	if (!collide("solid", x + (xspeed - (int)xspeed), y))
	{
		x += (xspeed - (int)xspeed);
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
	}
	else
	{
		yspeed = 0;
	}

	yspeed /= BEngine::elapsed;
}
