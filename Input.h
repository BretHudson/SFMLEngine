#ifndef _INPUT_H_
#define _INPUT_H_

#include <iostream>
#include <vector>

struct DefinedInput
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

		static void define(std::string name, int key, ...);

		static bool pressed(int key);
		static bool check(int key);
		static bool released(int key);

		static bool pressed(std::string name);
		static bool check(std::string name);
		static bool released(std::string name);

		static void updatePressed(int key);
		static void updateCheck(int key);
		static void updateReleased(int key);

		static std::vector<DefinedInput*> definedInputs;

	//private:
		static std::vector<int> keyState;
};

#endif
