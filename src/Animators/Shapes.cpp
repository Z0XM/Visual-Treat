#include "Shapes.hpp"
#include <iostream>

#include "BlinkingColors.hpp"

sf::Keyboard::Key Shapes::keyCode = sf::Keyboard::Q;

Shapes::Shapes(int radius, sf::Vector2f position)
	:position(position), radius(radius), points(4), revolution(sf::Transform::Identity), 
	state(SINGLE), activeRotation(false), rotateAnglePerSecond(0), blinkColors(false), revolve(false)
{
	this->shapes.push_back(sf::CircleShape(radius, points));
	this->shapes[0].setOrigin(radius, radius);
	this->shapes[0].setPosition(position);

	rotateKey = sf::Keyboard::R;
	revolveKey = sf::Keyboard::O;
	colorKey = sf::Keyboard::C;

	second = 0;
}

Shapes::~Shapes()
{
}

void Shapes::update(float dt)
{
	second += dt;
	if (second >= 0.05)second = 0;

	if (activeRotation) {
		for(auto &shape : shapes)
			shape.rotate(rotateAnglePerSecond * dt);
	}

	if (blinkColors && !second)
	{
		for (auto& shape : shapes) {
			shape.setFillColor(BlinkingColors::next(shape.getFillColor()));
		}
	}

	if (revolve)
	{
		revolution.rotate(5, this->position);
	}
}

void Shapes::draw(sf::RenderWindow& window)
{ 
	for (auto& shape : shapes) {
		window.draw(shape, revolution);
	}
}

sf::Vector2f Shapes::getPosition()
{
	return this->position;
}

void Shapes::resetRevolution()
{
	this->revolve = false;
	shapes.clear();
	shapes.push_back(sf::CircleShape(radius, points));
	this->shapes.back().setOrigin(radius, radius);
	this->shapes.back().setPosition(position);
}

void Shapes::setPointCount(unsigned int count)
{
	for (auto& shape : shapes){
		shape.setPointCount(count);
	}
	points = count;
}

void Shapes::setShapeCount(int stages)
{
	if (stages == 6) {
		if (shapes.back().getPosition() != position) {
			shapes.push_back(sf::CircleShape(radius, points));
			shapes.back().setOrigin(radius, radius);
			shapes.back().setPosition(position);
		}	
	}
	else {
		if (shapes.back().getPosition() == position)shapes.pop_back();
		else if (shapes.size() == 1 && stages > 1)shapes.pop_back();


		sf::Vector2f pos[8] = { {300, 0}, {-300, 0}, {0, 300}, {0, -300}, {300, 300}, {-300, -300}, {-300, 300}, {300, -300} };
		for (int i = 0; i < pow(2, stages - 1); i++) {
			if (i >= shapes.size()) {
				shapes.push_back(sf::CircleShape(radius, points));
				this->shapes.back().setOrigin(radius, radius);
			}
			this->shapes.back().setPosition(position + pos[i]);
		}
		if (shapes.size() > pow(2, stages - 1))shapes.erase(shapes.begin() + pow(2, stages - 1), shapes.end());
	}
}

void Shapes::setRotateAngle(int input)
{
	if (input == 1)
		this->rotateAnglePerSecond = -180;
	else if (input == 3)
		this->rotateAnglePerSecond = 180;
	else if (input == 4)
		this->rotateAnglePerSecond = -360;
	else if (input == 6)
		this->rotateAnglePerSecond = 360;
	else if (input == 7)
		this->rotateAnglePerSecond = -720;
	else if (input == 9)
		this->rotateAnglePerSecond = 720;
}

bool Shapes::handleKeyEvent(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(rotateKey)) {
		if (key == sf::Keyboard::Numpad5) {
			this->activeRotation = false;
			return true;
		}
		else if (key > sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9) {
			this->activeRotation = true;
			this->setRotateAngle(key - sf::Keyboard::Numpad0);
			return true;
		}
	}
	if (key == colorKey) {
		this->blinkColors = !this->blinkColors;
		return true;
	}
	if (sf::Keyboard::isKeyPressed(revolveKey)) {
		if (key == sf::Keyboard::Numpad5) { 
			this->revolve = !this->revolve;
			return true;
		}
		else if (key == sf::Keyboard::Numpad0) {
			this->resetRevolution();
			return true;
		}
		else if (key > sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad6) {
			this->revolve = true;
			this->setShapeCount(key - sf::Keyboard::Numpad0);
			return true;
		}
	}

	if (key >= sf::Keyboard::Numpad1 && key <= sf::Keyboard::Numpad9 && !sf::Keyboard::isKeyPressed(revolveKey) && !sf::Keyboard::isKeyPressed(rotateKey)){
		this->setPointCount(key - sf::Keyboard::Numpad0 + 2);
		return true;
	}
	
	return false;
}