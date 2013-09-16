#include "Input.h"

#include "BEngine.h"

#include <cstdarg>

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

void Input::define(const char* name, int key, ...)
{
	va_list arguments;

	for (va_start(arguments, key); key != NULL; key = va_arg(arguments, int))
	{
		BEngine::log(BEngine::itos(key));
	}

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
