#include "Spiral.hpp"
#include "BlinkingColors.hpp"

void Spiral::reset()
{
	second = 0;
	int factor = lines? 50 : 2;
	totalPoints = lines ? 20 : 250;

	BlinkingColors color;

	for (int i = 0; i < totalPoints; i++) {
		points[i][0].position = position + sf::Vector2f(-factor * i - factor, 0);
		points[i][1].position = position + sf::Vector2f(0, -factor * i - factor);
		points[i][2].position = position + sf::Vector2f(factor * i + factor, 0);
		points[i][3].position = position + sf::Vector2f(0, factor * i + factor);
		for (int j = 0; j < 4; j++) {
			points[i][j].color = color.getColor();
		}

		points[i][4] = points[i][0];

		color.next();
	}

	normalRotate = false;
	startRotate = false;

	rotateCounter = 0;

	revolution = sf::Transform::Identity;
}

Spiral::Spiral(sf::Vector2f position)
{
	this->position = position;
	this->speed = 5;
	this->lines = false;
	this->circles = false;
	this->reset();
}

Spiral::~Spiral()
{

}

void Spiral::update(float dt)
{
	second += dt;
	if (second >= 0.1)second = 0;
	if (!second)
	{
		for (int i = 0; i < totalPoints; i++){
			sf::Color color = BlinkingColors::next(points[i][0].color);
			for (int j = 0; j < 5; j++) {
				points[i][j].color = color;
			}
		}
	}

	if (startRotate) {
		for (int i = 0; i < 5; i++) {
			points[rotateCounter][i].position = revolution.transformPoint(points[rotateCounter][i].position);
		}
		rotateCounter++;
		if (rotateCounter == totalPoints) {
			normalRotate = true;
			startRotate = false;
		}
	}
	if (normalRotate || startRotate) {
		for (int i = 0; i < rotateCounter; i++) {
			for (int j = 0; j < 5; j++) {
				points[i][j].position = revolution.transformPoint(points[i][j].position);
			}
		}
	}
}

void Spiral::draw(sf::RenderWindow& window)
{
	sf::CircleShape circle(2);
	circle.setOrigin(2, 2);
	for (int i = 0; i < totalPoints; i++) {
		if (lines)window.draw(points[i], 5, sf::LineStrip);
		else if(circles){
			for (int j = 0; j < 4; j++) {
				circle.setPosition(points[i][j].position);
				circle.setFillColor(points[i][j].color);
				window.draw(circle);
			}
		}
		else window.draw(points[i], 4, sf::Points);
	}
}

bool Spiral::handleKeyEvent(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (key == sf::Keyboard::L) {
			startRotate = true;
			normalRotate = false;
			revolution = sf::Transform::Identity;
			revolution.rotate(speed, position);
			rotateCounter = 0;
			return true;
		}
		else if (key == sf::Keyboard::J) {
			startRotate = true;
			normalRotate = false;
			revolution = sf::Transform::Identity;
			revolution.rotate(-speed, position);
			rotateCounter = 0;
			return true;
		}
		else if (key == sf::Keyboard::K) {
			startRotate = false;
			normalRotate = false;
			return true;
		}
		else if (key == sf::Keyboard::R) {
			reset();
			return true;
		}
		else if (key == sf::Keyboard::I) {
			lines = !lines;
			reset();
			return true;
		}
		else if (key == sf::Keyboard::C) {
			circles = !circles;
			return true;
		}
		if (key >= sf::Keyboard::Numpad0 && sf::Keyboard::Numpad9) {
			speed = key - sf::Keyboard::Numpad0;
		}
	}
	return false;
}

void Spiral::startRotation()
{
	startRotate = true;
	rotateCounter = 0;
}