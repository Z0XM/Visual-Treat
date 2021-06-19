#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

namespace Music {
	void load(sf::Music& music, int musicIndex = 0);
	bool handleKeyEvent(sf::Music& music, sf::Keyboard::Key);

	extern sf::Keyboard::Key keyCode;
}