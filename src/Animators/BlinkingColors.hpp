#pragma once

#include <SFML/Graphics.hpp>

class BlinkingColors {
	sf::Color current;

public:
	BlinkingColors();

	void next();
	void reset();

	sf::Color getColor();

	static sf::Color next(sf::Color);
};
