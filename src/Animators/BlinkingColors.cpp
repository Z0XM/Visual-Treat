#include "BlinkingColors.hpp"

BlinkingColors::BlinkingColors()
{
	current = sf::Color::White;
}

void BlinkingColors::next()
{
	if (current == sf::Color::White)current = sf::Color::Yellow;
	else if (current == sf::Color::Yellow)current = sf::Color::Red;
	else if (current == sf::Color::Red)current = sf::Color::Magenta;
	else if (current == sf::Color::Magenta)current = sf::Color::Blue;
	else if (current == sf::Color::Blue)current = sf::Color::Cyan;
	else if (current == sf::Color::Cyan)current = sf::Color::White;
}

void BlinkingColors::reset()
{
	current = sf::Color::White;
}

sf::Color BlinkingColors::getColor()
{
	return current;
}

sf::Color BlinkingColors::next(sf::Color color)
{
	if (color == sf::Color::White)return sf::Color::Yellow;
	if (color == sf::Color::Yellow)return sf::Color::Red;
	if (color == sf::Color::Red)return sf::Color::Magenta;
	if (color == sf::Color::Magenta)return sf::Color::Blue;
	if (color == sf::Color::Blue)return sf::Color::Cyan;
	if (color == sf::Color::Cyan)return sf::Color::White;
}
