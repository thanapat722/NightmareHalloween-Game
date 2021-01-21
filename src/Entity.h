#pragma once
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
class Entity
{
public:
	Entity();
	~Entity();
	sf::RectangleShape body;
	sf::Sprite sprite;
	sf::Text text;
};

