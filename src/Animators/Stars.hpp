#pragma once 
#include <SFML/Graphics.hpp>

class Stars
{
	sf::Vector2f points[100];
	sf::Color colors[100];
	float zFactor[100];
	float theta;
	float rotateConstant;
	float speed;

	sf::Keyboard::Key rightKey, leftKey, stopKey, fastKey, slowKey, normalSpeedKey;

	sf::Vector2f winSize;

public:
	Stars(const sf::Vector2f& winSize);
	~Stars();

	bool handleKeyEvent(sf::Keyboard::Key key);

	void update(float dt);
	void draw(sf::RenderWindow&);

	static sf::Keyboard::Key keyCode;
};
