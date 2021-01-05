#pragma once
#include <SFML/Graphics.hpp>
#include "Animators.hpp"

class SFML_Control {
private:
	sf::RenderWindow window;
	bool running;
	bool pauseSystem;
	sf::Clock clock;

	Shapes* shapeAnim;
	Spiral* spiral;
	Canvas* canvas;

	void InitWindow();
	void InitShapeAnim();
	void InitSpiral();
	void InitCanvas();
public:
	SFML_Control();
	~SFML_Control();

	bool isRunning();

	void update();
	void pollEvents();
	void render();

	sf::Vector2f getMousePosition();
	sf::Vector2f getWinSize();
};
