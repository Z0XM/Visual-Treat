#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animators.hpp"
#include "MusicControl.hpp"

class SFML_Control {
private:
	sf::RenderWindow window;
	bool running;
	bool pauseSystem;
	sf::Clock clock;


	Shapes* shapeAnim;
	Spiral* spiral;
	Canvas* canvas;
	Stars* stars;
	
	sf::Music music;
	sf::Texture lightTexture;

	void InitWindow();
	void InitShapeAnim();
	void InitSpiral();
	void InitCanvas();
	void InitStars();
	void InitNewLight();
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
