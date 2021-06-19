#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
class Canvas {
	std::deque<sf::Vertex> trail;

	int trailCount;
	bool pauseTrail;
	sf::PrimitiveType type;

	sf::Keyboard::Key colorKey;
public:

	Canvas();

	void update(sf::Vector2f position);
	void draw(sf::RenderWindow& window);

	bool handleKeyEvent(sf::Keyboard::Key key);

	static sf::Keyboard::Key keyCode;
};