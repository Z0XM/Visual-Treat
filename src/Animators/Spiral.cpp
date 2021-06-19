#include "Spiral.hpp"
#include "BlinkingColors.hpp"

sf::Keyboard::Key Spiral::keyCode = sf::Keyboard::S;

void Spiral::reset()
{
	second = 0;
	int factor = lines? 25 : 2;
	totalPoints = lines ? 40 : 250;
	int colorWidth = lines ? 5 : 10;

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

		if(i%colorWidth == 0)color.prev();
	}

	normalRotate = false;
	startRotate = false;

	rotateCounter = 0;

	revolution = sf::Transform::Identity;

	leftKey = sf::Keyboard::J;
	rightKey = sf::Keyboard::L;
	resetKey = sf::Keyboard::R;
	stopKey = sf::Keyboard::K;
	switchModeKey = sf::Keyboard::I;
	colorKey = sf::Keyboard::C;
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
	sf::RectangleShape circle({ 3, 3 });
	circle.setOrigin(1.5, 1.5);
	for (int i = 0; i < totalPoints; i++) {
		if (lines)window.draw(points[i], 5, lines == 1? sf::Lines : sf::LinesStrip);
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
	if (sf::Keyboard::isKeyPressed(keyCode)) {
		if (key == rightKey) {
			startRotate = true;
			normalRotate = false;
			revolution = sf::Transform::Identity;
			revolution.rotate(speed, position);
			rotateCounter = 0;
			return true;
		}
		else if (key == leftKey) {
			startRotate = true;
			normalRotate = false;
			revolution = sf::Transform::Identity;
			revolution.rotate(-speed, position);
			rotateCounter = 0;
			return true;
		}
		else if (key == stopKey) {
			startRotate = false;
			normalRotate = false;
			return true;
		}
		else if (key == resetKey) {
			reset();
			return true;
		}
		else if (key == switchModeKey) {
			lines = (lines+1)%3;
			reset();
			return true;
		}
		else if (key == colorKey) {
			circles = !circles;
			return true;
		}
		if (key > sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9) {
			speed = key - sf::Keyboard::Numpad0;
			return true;
		}
	}
	return false;
}

void Spiral::startRotation()
{
	startRotate = true;
	rotateCounter = 0;
}