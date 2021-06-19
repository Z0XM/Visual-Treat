#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Light {
	sf::Sprite img;
	float lifetime;
	bool diminish;
public:

	static void add(sf::Texture& tex, const sf::Vector2f&);
	static void update(float dt);
	static void draw(sf::RenderWindow& win);
	static void destroy();

	static std::vector<Light*> Group;
	static sf::Keyboard::Key keyCode;
};