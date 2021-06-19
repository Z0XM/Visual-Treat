#include "MusicControl.hpp"


void Music::load(sf::Music& music, int musicIndex)
{
	music.openFromFile("data/capricorn.wav");
	music.setVolume(50);
	music.play();
}

sf::Keyboard::Key playPauseKey = sf::Keyboard::P;

bool Music::handleKeyEvent(sf::Music& music, sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::P) {
		if (music.getStatus() != sf::Music::Playing)music.play();
		else music.pause();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && key > sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9) {
		music.setPitch(key - sf::Keyboard::Numpad0);
	}
	return false;
}

extern sf::Keyboard::Key Music::keyCode = sf::Keyboard::M;