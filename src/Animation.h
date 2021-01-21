#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

void Update(int row, float deltaTime,bool faceRight, int type);

public:
	sf::IntRect uvRect;
	bool endAnimation;
	sf::Vector2u currentImage;
	int attackCount;

private:
	sf::Vector2u imageCount;
	int row;
	float totalTime;
	float switchTime;
};