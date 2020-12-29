#include "SFML_Control.hpp"
#include <iostream>

void SFML_Control::InitWindow()
{
	window.create(sf::VideoMode(1200, 700), "mazeGame");
	window.setFramerateLimit(60);
}

void SFML_Control::InitShapeAnim()
{
	this->shapeAnim = new Shapes(100, this->getWinSize() * 0.5f);
	this->shapeAnim->setPointCount(4);
}

void SFML_Control::InitSpiral()
{
	this->spiral = new Spiral(this->getWinSize() * 0.5f);
}

SFML_Control::SFML_Control()
{
	this->clock.restart();

	this->InitWindow();

	running = true;
	pauseSystem = false;
	
	this->shapeAnim = nullptr;
	this->spiral = nullptr;
}

SFML_Control::~SFML_Control()
{

}

bool SFML_Control::isRunning()
{
	return this->running;
}

void SFML_Control::update()
{
	this->pollEvents();
	if (!pauseSystem) {
		if (this->shapeAnim != nullptr)this->shapeAnim->update(clock.getElapsedTime().asSeconds());
		if (this->spiral != nullptr)this->spiral->update(clock.getElapsedTime().asSeconds());
		this->clock.restart();
	}
}

void SFML_Control::pollEvents()
{
	sf::Event event;
	sf::Vector2f mousePos = this->getMousePosition();
	while (this->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->running = false;

		if (event.type == sf::Event::MouseButtonPressed) {

		}
		else if (event.type == sf::Event::MouseButtonReleased) {

		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space)pauseSystem = !pauseSystem;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				if (shapeAnim == nullptr)this->InitShapeAnim();
				else if (!shapeAnim->handleKeyEvent(event.key.code) && event.key.code == sf::Keyboard::Numpad0) {
					delete shapeAnim;
					shapeAnim = nullptr;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if (spiral == nullptr)this->InitSpiral();
				else if (!spiral->handleKeyEvent(event.key.code) && event.key.code == sf::Keyboard::Numpad0) {
					delete spiral;
					spiral = nullptr;
				}
			}
		}
	}
}

void SFML_Control::render()
{
	this->window.clear();

	if (this->shapeAnim != nullptr)shapeAnim->draw(window);
	if (this->spiral != nullptr)spiral->draw(window);

	this->window.display();
}

sf::Vector2f SFML_Control::getMousePosition()
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
}

sf::Vector2f SFML_Control::getWinSize()
{
	return sf::Vector2f(this->window.getSize());
}