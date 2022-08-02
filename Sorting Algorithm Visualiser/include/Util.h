#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>

namespace util {

	struct Settings
	{
		Settings();
		bool isSorted, isShuffled, isAppRunning, generateNewList;
		int selected;
	};
};