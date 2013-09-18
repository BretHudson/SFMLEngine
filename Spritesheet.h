#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include <SFML/Graphics.hpp>

/*class Strip
{
	public:
		Strip();
		std::string name;
		std::vector<int> keys;
};*/

class Spritesheet
{
	public:
		Spritesheet(std::string file, int width, int height);

		void add(std::string name, int frames[]);
		virtual void update();

		sf::Texture* getTexture();
		sf::Sprite* getSprite();

		sf::Texture texture;
		sf::Sprite sprite;

		int width, height;
		int columns, rows;
		int frame;
};

#endif

