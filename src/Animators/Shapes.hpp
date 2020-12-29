#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Shapes
{
	sf::Vector2f position;
	int radius;
	unsigned int points;
	sf::Transform revolution;

	float second;

public:
	Shapes(int radius, sf::Vector2f position);
	~Shapes();

	enum States{SINGLE = 0};
	States state;

	void update(float dt);
	void draw(sf::RenderWindow&);

	void resetRevolution();
	sf::Vector2f getPosition();

	void setPointCount(unsigned int count);
	void setShapeCount(int count);
	void setRotateAngle(int input);

	bool handleKeyEvent(sf::Keyboard::Key key);

	std::vector<sf::CircleShape> shapes;
	bool activeRotation;
	float rotateAnglePerSecond;
	bool blinkColors;
	bool revolve;
};
