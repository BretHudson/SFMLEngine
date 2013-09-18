#include "Input.h"

#include "BEngine.h"

#include <cstdarg>

std::vector<int> Input::keyState;
std::vector<int> Input::joystickState;
std::vector<DefinedKeyInput*> Input::definedKeyInputs;
std::vector<DefinedJoystickInput*> Input::definedJoystickInputs;
std::vector<DefinedJoystickAxis*> Input::definedJoystickAxes;

DefinedKeyInput::DefinedKeyInput()
{
	//
}

DefinedJoystickInput::DefinedJoystickInput()
{
	//
}

DefinedJoystickAxis::DefinedJoystickAxis()
{
	//
}

void Input::init()
{
	keyState.resize(sf::Keyboard::KeyCount);
	std::vector<int>::iterator keyStateIterator;

	for (keyStateIterator = keyState.begin(); keyStateIterator != keyState.end(); keyStateIterator++)
	{
		*keyStateIterator = -1;
	}

	joystickState.resize(sf::Joystick::ButtonCount);
	std::vector<int>::iterator joystickStateIterator;

	for (joystickStateIterator = joystickState.begin(); joystickStateIterator != joystickState.end(); joystickStateIterator++)
	{
		*joystickStateIterator = -1;
	}
}

void Input::reset()
{
	std::vector<int>::iterator keyStateIterator;

	for (keyStateIterator = keyState.begin(); keyStateIterator != keyState.end(); keyStateIterator++)
	{
		if (*keyStateIterator == 0)
			*keyStateIterator = 1;
		if (*keyStateIterator == 2)
			*keyStateIterator = -1;
	}

	std::vector<int>::iterator joystickStateIterator;

	for (joystickStateIterator = joystickState.begin(); joystickStateIterator != joystickState.end(); joystickStateIterator++)
	{
		if (*joystickStateIterator == 0)
			*joystickStateIterator = 1;
		if (*joystickStateIterator == 2)
			*joystickStateIterator = -1;
	}
}

void Input::define(std::string name, int key, ...)
{
	va_list arguments;

	DefinedKeyInput* input = new DefinedKeyInput();
	input->name = name;

	for (va_start(arguments, key); key != NULL; key = va_arg(arguments, int))
	{
		if (key > sf::Keyboard::KeyCount)
			break;
		input->keys.push_back(key);
	}

	definedKeyInputs.push_back(input);
}

void Input::defineJoystick(std::string name, int id, int button, ...)
{
	va_list arguments;

	DefinedJoystickInput* input = new DefinedJoystickInput();
	input->name = name;
	input->id = id;

	for (va_start(arguments, button); (button != NULL) && (button != 0); button = va_arg(arguments, int))
	{
		if (button - 1 > sf::Joystick::ButtonCount)
			break;
		input->buttons.push_back(button - 1);
	}

	definedJoystickInputs.push_back(input);
}

void Input::defineJoystickAxis(std::string neg, std::string pos, int axis, float sensitivity)
{
	DefinedJoystickAxis* _axis = new DefinedJoystickAxis();
	_axis->neg = neg;
	_axis->pos = pos;
	_axis->axis = axis;
	_axis->sensitivity = sensitivity;

	definedJoystickAxes.push_back(_axis);
}

bool Input::pressed(int key)
{
	return (keyState[key] == 0);
}

bool Input::check(int key)
{
	return (keyState[key] == 1);
}

bool Input::released(int key)
{
	return (keyState[key] == 2);
}

bool Input::pressedJoystick(int id, int button)
{
	return (joystickState[button] == 0);
}

bool Input::checkJoystick(int id, int button)
{
	return (joystickState[button] == 1);
}

bool Input::releasedJoystick(int id, int button)
{
	return (joystickState[button] == 2);
}

bool Input::pressed(std::string name)
{
	std::vector<DefinedKeyInput*>::iterator definedKeysIterator;
	std::vector<DefinedJoystickInput*>::iterator definedJoysticksIterator;

	for (definedKeysIterator = definedKeyInputs.begin(); definedKeysIterator != definedKeyInputs.end(); definedKeysIterator++)
	{
		if ((*definedKeysIterator)->name == name)
		{
			// Check keys
			for (int i = 0; i < (*definedKeysIterator)->keys.size(); i++)
			{
				if (pressed((*definedKeysIterator)->keys[i]))
					return true;
			}
		}
	}

	for (definedJoysticksIterator = definedJoystickInputs.begin(); definedJoysticksIterator != definedJoystickInputs.end(); definedJoysticksIterator++)
	{
		if ((*definedJoysticksIterator)->name == name)
		{
			//BEngine::log(BEngine::itos((*definedJoysticksIterator)->buttons.size()) + " " + (*definedJoysticksIterator)->name);
			// Check Buttons
			for (int i = 0; i < (*definedJoysticksIterator)->buttons.size(); i++)
			{
				for (int id = 0; id < 5; id++)
				{
					if (pressedJoystick(id, (*definedJoysticksIterator)->buttons[i]))
						return true;
				}
			}
		}
	}

	return false;
}

bool Input::check(std::string name)
{
	std::vector<DefinedKeyInput*>::iterator definedKeysIterator;
	std::vector<DefinedJoystickInput*>::iterator definedJoysticksIterator;
	std::vector<DefinedJoystickAxis*>::iterator definedAxesIterator;

	for (definedKeysIterator = definedKeyInputs.begin(); definedKeysIterator != definedKeyInputs.end(); definedKeysIterator++)
	{
		if ((*definedKeysIterator)->name == name)
		{
			// Check keys
			for (int i = 0; i < (*definedKeysIterator)->keys.size(); i++)
			{
				if (check((*definedKeysIterator)->keys[i]))
					return true;
			}
		}
	}

	for (definedJoysticksIterator = definedJoystickInputs.begin(); definedJoysticksIterator != definedJoystickInputs.end(); definedJoysticksIterator++)
	{
		if ((*definedJoysticksIterator)->name == name)
		{
			// Check Buttons
			for (int i = 0; i < (*definedJoysticksIterator)->buttons.size(); i++)
			{
				for (int id = 0; id < 5; id++)
				{
					if (checkJoystick(id, (*definedJoysticksIterator)->buttons[i]))
						return true;
				}
			}
		}
	}

	for (definedAxesIterator = definedJoystickAxes.begin(); definedAxesIterator != definedJoystickAxes.end(); definedAxesIterator++)
	{
		if ((*definedAxesIterator)->neg == name)
		{
			for (int i = 0; i < 5; i++)
			{
				if (sf::Joystick::getAxisPosition(i, sf::Joystick::X) < -(*definedAxesIterator)->sensitivity)
					return true;
			}
		}
		else if ((*definedAxesIterator)->pos == name)
		{
			for (int i = 0; i < 5; i++)
			{
				if (sf::Joystick::getAxisPosition(i, sf::Joystick::X) > (*definedAxesIterator)->sensitivity)
					return true;
			}
		}
	}

	return false;
}

bool Input::released(std::string name)
{
	std::vector<DefinedKeyInput*>::iterator definedKeysIterator;
	std::vector<DefinedJoystickInput*>::iterator definedJoysticksIterator;

	for (definedKeysIterator = definedKeyInputs.begin(); definedKeysIterator != definedKeyInputs.end(); definedKeysIterator++)
	{
		if ((*definedKeysIterator)->name == name)
		{
			// Check keys
			for (int i = 0; i < (*definedKeysIterator)->keys.size(); i++)
			{
				if (released((*definedKeysIterator)->keys[i]))
					return true;
			}
		}
	}

	for (definedJoysticksIterator = definedJoystickInputs.begin(); definedJoysticksIterator != definedJoystickInputs.end(); definedJoysticksIterator++)
	{
		if ((*definedJoysticksIterator)->name == name)
		{
			// Check Buttons
			for (int i = 0; i < (*definedJoysticksIterator)->buttons.size(); i++)
			{
				for (int id = 0; id < 5; id++)
				{
					if (releasedJoystick(id, (*definedJoysticksIterator)->buttons[i]))
						return true;
				}
			}
		}
	}

	return false;
}

void Input::updatePressed(int key)
{
	keyState[key] = 0;
}

void Input::updateCheck(int key)
{
	keyState[key] = 1;
}

void Input::updateReleased(int key)
{
	keyState[key] = 2;
}

void Input::updateJoystickPressed(int id, int button)
{
	joystickState[button] = 0;
}

void Input::updateJoystickCheck(int id, int button)
{
	joystickState[button] = 1;
}

void Input::updateJoystickReleased(int id, int button)
{
	joystickState[button] = 2;
}
