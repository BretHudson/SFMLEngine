#ifndef _INPUT_H_
#define _INPUT_H_

#include <iostream>
#include <vector>

struct Define
{
	public:
		std::string name;
		std::vector<int> keys;
};

class Input
{
	public:
		static void init();
		static void reset();

		static void define(const char* name, int key, ...);

		static bool pressed(int key);
		static bool check(int key);
		static bool released(int key);

		static void updatePressed(int key);
		static void updateCheck(int key);
		static void updateReleased(int key);
	private:
		static std::vector<int> keyState;
};

#endif
