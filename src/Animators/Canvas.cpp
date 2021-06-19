#include "Canvas.hpp"
#include "BlinkingColors.hpp"

sf::Keyboard::Key Canvas::keyCode = sf::Keyboard::X;

Canvas::Canvas()
{
	pauseTrail = false;
	trailCount = 100;
	type = sf::Points;

	colorKey = sf::Keyboard::C;

	int color_count = trailCount / 6;
	BlinkingColors color;
	for (int i = 0; i < trailCount; i++) {
		if (i % color_count == 0 && i != trailCount - trailCount % color_count)color.next();
		trail.push_back(sf::Vertex(sf::Vector2f(), color.getColor()));
	}
}

void Canvas::update(sf::Vector2f position)
{
	if (!pauseTrail) {
		trail.pop_front();
		trail.push_back(sf::Vertex(position, trail.back().color));
	}
	else {
		sf::Vertex v = trail[0];
		trail.pop_front();
		trail.push_back(v);
	}
	for (int i = trailCount / 6 - 1; i < trailCount - trailCount%6; i += trailCount / 6) {
		trail[i].color = BlinkingColors::next(trail[i].color);
	}
}

void Canvas::draw(sf::RenderWindow& window)
{
	sf::Vertex t[100];

	for (int i = 0; i < trailCount; i++) {
		t[i] = trail[i];
	}

	if (type != sf::LineStrip)window.draw(t, 100, sf::LineStrip);
	window.draw(t, 100, type);
}

bool Canvas::handleKeyEvent(sf::Keyboard::Key key)
{
	if (key == colorKey) {
		pauseTrail = !pauseTrail;
	}
	else if (key == sf::Keyboard::Numpad1 || key == sf::Keyboard::Num1)type = sf::LineStrip;
	else if (key == sf::Keyboard::Numpad2 || key == sf::Keyboard::Num2)type = sf::Triangles;
	else if (key == sf::Keyboard::Numpad3 || key == sf::Keyboard::Num3)type = sf::TrianglesStrip;
	else if (key == sf::Keyboard::Numpad4 || key == sf::Keyboard::Num4)type = sf::Quads;

	return false;
}
