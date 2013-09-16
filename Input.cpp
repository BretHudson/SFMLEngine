#include "Input.h"

#include "BEngine.h"

#include <cstdarg>

std::vector<DefinedInput*> definedInputs;
std::vector<int> Input::keyState;


void Input::init()
{
	Input::keyState.resize(sf::Keyboard::KeyCount);
	std::vector<int>::iterator keyStateIterator;

	for (keyStateIterator = keyState.begin(); keyStateIterator != keyState.end(); keyStateIterator++)
	{
		*keyStateIterator = -1;
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
}

void Input::define(std::string name, int key, ...)
{
	va_list arguments;

	DefinedInput input;

	for (va_start(arguments, key); key != NULL; key = va_arg(arguments, int))
	{
		if (key > sf::Keyboard::KeyCount)
			break;
		input.keys.push_back(key);
	}

	//definedInputs.push_back(&input);
	keyState[key];
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

bool Input::pressed(std::string name)
{
	std::vector<DefinedInput*>::iterator definedInputsItertor;

	for (definedInputsItertor = definedInputs.begin(); definedInputsItertor != definedInputs.end(); definedInputsItertor++)
	{
		if ((*definedInputsItertor)->name == name)
		{
			for (int i = 0; i < (*definedInputsItertor)->keys.size(); i++)
			{
				if ((*definedInputsItertor)->keys[i] == 0)
					return true;
			}
		}
	}

	return false;
}

bool Input::check(std::string name)
{
	/*return (keyState[key] == 1);*/
	return false;
}

bool Input::released(std::string name)
{
	/*return (keyState[key] == 2);*/
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
