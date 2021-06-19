#include "Light.hpp"
#include "BlinkingColors.hpp"

std::vector<Light*> Light::Group;
sf::Keyboard::Key Light::keyCode = sf::Keyboard::A;

void Light::add(sf::Texture& tex, const sf::Vector2f& winSize)
{
	Light* light = new Light();
	Group.push_back(light);
	light->img.setTexture(tex);
	light->img.setOrigin(light->img.getGlobalBounds().width / 2, light->img.getGlobalBounds().height / 2);
	light->img.setPosition((rand() % (int)(winSize.x - 100)) + 50, (rand() % (int)(winSize.y - 100)) + 50);
	light->img.setRotation(rand() % 360);
	light->img.setColor(BlinkingColors::random());
	light->diminish = false;
	light->lifetime = 1;
}

void Light::update(float dt)
{
	for (auto it = Group.begin(); it != Group.end();)
	{
		(*it)->lifetime -= dt;

		if ((*it)->lifetime <= 0 && !(*it)->diminish) {
			(*it)->diminish = true;
			it++;
		}
		else if ((*it)->diminish) {
			sf::FloatRect fr = (*it)->img.getGlobalBounds();
			(*it)->img.scale(0.8, 0.8);
			if (fr.width < 10) {
				delete* it;
				it = Group.erase(it);
			}
			else it++;
		}
		else it++;
	}
}

void Light::draw(sf::RenderWindow& win)
{
	for (int i = 0; i < Group.size(); i++)
	{
		win.draw(Group[i]->img, sf::BlendAdd);
	}
}

void Light::destroy()
{
	for (auto it = Group.begin(); it != Group.end(); it++){
		delete* it;
	}
	Group.clear();
}
