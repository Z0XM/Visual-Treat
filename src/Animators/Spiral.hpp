#pragma once

#include <SFML/Graphics.hpp>

class Spiral {
	sf::Vertex points[250][5];
	sf::Vector2f position;

	float second;
	float rotateAnglePerSecond;
	sf::Transform revolution;
	int totalPoints;

	bool normalRotate;
	bool startRotate;
	int rotateCounter;
	int speed;

	bool circles;
	bool lines;
public:
	Spiral(sf::Vector2f position);
	~Spiral();

	void update(float dt);
	void draw(sf::RenderWindow& window);

	void startRotation();

	bool handleKeyEvent(sf::Keyboard::Key key);
	void reset();
};