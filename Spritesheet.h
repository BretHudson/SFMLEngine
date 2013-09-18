#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include <SFML/Graphics.hpp>

class Strip
{
	public:
		Strip(std::string name, int frames[], int framecount, int speed, bool loop);

		void update();
		int getFrame();

		std::string name;
		std::vector<int> frames;
		float framecount;
		bool loop;
		int frame;
		float speed;
		float elapsed;
};

class Spritesheet
{
	public:
		Spritesheet(std::string file, int width, int height);

		void add(std::string name, int frames[], int framecount, int speed);
		void add(std::string name, int frames[], int framecount, int speed, bool loop);
		void play(std::string name);
		void play(std::string name, bool reset);
		virtual void update();

		sf::Texture* getTexture();
		sf::Sprite* getSprite();

	private:
		sf::Texture texture;
		sf::Sprite sprite;

		Strip* curStrip;
		std::vector<Strip*> strips;

		int width, height;
		int columns, rows;
};

#endif

