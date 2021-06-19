#include "Stars.hpp"
#include "BlinkingColors.hpp"

#include <iostream>

sf::Keyboard::Key Stars::keyCode = sf::Keyboard::Z;

Stars::Stars(const sf::Vector2f& winSize)
	:winSize(winSize)
{
	for (int i = 0; i < 100; i++)
	{
		points[i] = {
			float(rand() % ((int)winSize.x + 500) - winSize.x / 2 - 250),
			float(rand() % ((int)winSize.y + 500) - winSize.y / 2 - 250)
		};
		zFactor[i] = rand() % 10 + 10;
		colors[i] = BlinkingColors::random();
	}

	theta = 0.0f;
	rotateConstant = 0.001;
	speed = 1;
	rightKey = sf::Keyboard::L;
	leftKey = sf::Keyboard::J;
	stopKey = sf::Keyboard::K;
	fastKey = sf::Keyboard::Up;
	slowKey = sf::Keyboard::Down;
	normalSpeedKey = sf::Keyboard::R;
}

Stars::~Stars()
{
}

bool Stars::handleKeyEvent(sf::Keyboard::Key key)
{
	if (sf::Keyboard::isKeyPressed(keyCode)) {
		if (key == leftKey) {
			theta -= rotateConstant;
		}
		else if (key == rightKey){
			theta += rotateConstant;
		}
		else if (key == stopKey) {
			theta = 0.0f;
		}
		else if (key == fastKey){
			speed++;
		}
		else if (key == slowKey) {
			speed--;
		}
		else if (key == normalSpeedKey) {
			speed = 1;
		}
	}

	return false;
}

void Stars::update(float dt)
{
	for (int i = 0; i < 100; i++) {
		zFactor[i] -= speed*dt;
		if (zFactor[i] <= 1) {
			points[i] = {
				float(rand() % ((int)winSize.x + 500) - winSize.x / 2 - 250),
				float(rand() % ((int)winSize.y + 500) - winSize.y / 2 - 250)
			};
			zFactor[i] = rand() % 10 + 10;
		}
		else if (speed < 0 && zFactor[i] >= 15) {
			points[i] = {
				float(rand() % ((int)winSize.x + 500) - winSize.x / 2 - 250),
				float(rand() % ((int)winSize.y + 500) - winSize.y / 2 - 250)
			};
			zFactor[i] = 1;
		}
		points[i].x = points[i].x * cos(theta) - points[i].y * sin(theta);
		points[i].y = points[i].x * sin(theta) + points[i].y * cos(theta);
	}
}

void Stars::draw(sf::RenderWindow& window)
{	
	for (int i = 0; i < 100; i++) {
		sf::Vector2f p(points[i].x / (1 - zFactor[i]), points[i].y / (1 - zFactor[i]));
		sf::CircleShape circle(20/zFactor[i]);
		circle.setOrigin(circle.getRadius()/2, circle.getRadius()/2);
		circle.setPosition(p.x + winSize.x/2, p.y + winSize.y/2);
		circle.setFillColor(colors[i]);
		window.draw(circle, sf::BlendAdd);
	}
}
