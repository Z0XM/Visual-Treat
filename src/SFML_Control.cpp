#include "SFML_Control.hpp"
#include <iostream>

void SFML_Control::InitWindow()
{
	window.create(sf::VideoMode(1200, 700), "Visual Treat");
	window.setFramerateLimit(60);
	this->window.setMouseCursorVisible(false);
	this->window.setKeyRepeatEnabled(false);
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

void SFML_Control::InitCanvas()
{
	this->canvas = new Canvas();
}

void SFML_Control::InitStars()
{
	this->stars = new Stars(this->getWinSize());
}

void SFML_Control::InitNewLight()
{
	Light::add(lightTexture, this->getWinSize());
}

SFML_Control::SFML_Control()
{
	this->clock.restart();

	this->InitWindow();

	running = true;
	pauseSystem = false;
	
	this->shapeAnim = nullptr;
	this->spiral = nullptr;
	this->canvas = nullptr;
	this->stars = nullptr;

	lightTexture.loadFromFile("data/star.png");
}

SFML_Control::~SFML_Control()
{
	Light::destroy();
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
		if (this->canvas != nullptr)this->canvas->update(this->getMousePosition());
		if (this->stars != nullptr)this->stars->update(clock.getElapsedTime().asSeconds());
		Light::update(clock.getElapsedTime().asSeconds());
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
			if(event.key.code == sf::Keyboard::Escape)this->running = false;

			if (event.key.code == sf::Keyboard::Space)pauseSystem = !pauseSystem;

			if (sf::Keyboard::isKeyPressed(Shapes::keyCode)) {
				if (shapeAnim == nullptr)this->InitShapeAnim();
				else if (!shapeAnim->handleKeyEvent(event.key.code) && event.key.code == sf::Keyboard::Numpad0) {
					delete shapeAnim;
					shapeAnim = nullptr;
				}
			}

			if (sf::Keyboard::isKeyPressed(Spiral::keyCode)) {
				if (spiral == nullptr)this->InitSpiral();
				else if (!spiral->handleKeyEvent(event.key.code) && event.key.code == sf::Keyboard::Numpad0) {
					delete spiral;
					spiral = nullptr;
				}
			}

			if (sf::Keyboard::isKeyPressed(Canvas::keyCode)) {
				if (canvas == nullptr)this->InitCanvas();
				else if(!canvas->handleKeyEvent(event.key.code) && event.key.code == sf::Keyboard::Numpad0) {
					delete canvas;
					canvas = nullptr;
				}
			}

			if (sf::Keyboard::isKeyPressed(Stars::keyCode)) {
				if (stars == nullptr)this->InitStars();
				else if (!stars->handleKeyEvent(event.key.code) && event.key.code == sf::Keyboard::Numpad0) {
					delete stars;
					stars = nullptr;
				}
			}

			if (sf::Keyboard::isKeyPressed(Music::keyCode)) {
				if (music.getStatus() == sf::Music::Stopped)Music::load(music);
				Music::handleKeyEvent(music, event.key.code);
				if(event.key.code == sf::Keyboard::Numpad0)music.stop();
			}

			if (event.key.code == Light::keyCode) {
				this->InitNewLight();
			}
		}
	}
}

void SFML_Control::render()
{
	this->window.clear();

	if (this->shapeAnim != nullptr)shapeAnim->draw(window);
	if (this->spiral != nullptr)spiral->draw(window);
	if (this->canvas != nullptr)canvas->draw(window);
	if (this->stars != nullptr)stars->draw(window);
	Light::draw(window);

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