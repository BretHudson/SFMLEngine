#ifndef _INPUT_H_
#define _INPUT_H_

#include <iostream>
#include <vector>

class DefinedKeyInput
{
	public:
		DefinedKeyInput();
		std::string name;
		std::vector<int> keys;
};

class DefinedJoystickInput
{
	public:
		DefinedJoystickInput();
		int id;
		std::string name;
		std::vector<int> buttons;
};

class DefinedJoystickAxis
{
	public:
		DefinedJoystickAxis();
		std::string neg;
		std::string pos;
		int axis;
		float sensitivity;
};

class Input
{
	public:
		static void init();
		static void reset();

		static void define(std::string name, int key, ...);
		static void defineJoystick(std::string name, int id, int button, ...);
		static void defineJoystickAxis(std::string neg, std::string pos, int axis, float sensitivity);

		static bool pressed(int key);
		static bool check(int key);
		static bool released(int key);

		static bool pressedJoystick(int id, int button);
		static bool checkJoystick(int id, int button);
		static bool releasedJoystick(int id, int button);

		static bool pressed(std::string name);
		static bool check(std::string name);
		static bool released(std::string name);

		static void updatePressed(int key);
		static void updateCheck(int key);
		static void updateReleased(int key);

		static void updateJoystickPressed(int id, int button);
		static void updateJoystickCheck(int id, int button);
		static void updateJoystickReleased(int id, int button);

	//private:
		static std::vector<int> keyState;
		static std::vector<int> joystickState;
		static std::vector<DefinedKeyInput*> definedKeyInputs;
		static std::vector<DefinedJoystickInput*> definedJoystickInputs;
		static std::vector<DefinedJoystickAxis*> definedJoystickAxes;
};

#endif
