#ifndef _BENGINE_H_
#define _BENGINE_H_

#include "World.h"

#include <SFML/Graphics.hpp>

/*class BEngine
{
	public:
		BEngine();
		void log(sf::String s);
		void update();
		void render(sf::RenderWindow* Window);

		void setWorld(World* w);

	private:
		World* _world;
};*/

/*class BEngine
{
    public:
        static BEngine& getInstance()
        {
            static BEngine instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
        static void log(sf::String s);
		static void update();
		static void render(sf::RenderWindow* Window);

		static World* world();
		static void world(World* w);
		static World* _world;

    private:
        BEngine() {};                   // Constructor? (the {} brackets) are needed here.
        // Dont forget to declare these two. You want to make sure they
        // are unaccessable otherwise you may accidently get copies of
        // your singleton appearing.
        BEngine(BEngine const&);              // Don't Implement
        void operator=(BEngine const&); // Don't implement
};*/

namespace BEngine
{
	extern World* _world;

	extern sf::Clock _deltaClock;
	extern sf::Time _deltaTime;
	extern int framerate;
	extern float elapsed;

	extern sf::View camera;

	extern void log(sf::String s);
	extern void error(sf::String s);
	extern void update();
	extern void render(sf::RenderWindow* Window);

	extern World* world();
	extern void world(World* w);

	extern int sign(float n);
	extern std::string itos(int n);
	extern std::string ftos(float n);
}

#endif
