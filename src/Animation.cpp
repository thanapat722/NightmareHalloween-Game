#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	row = 0;
	totalTime = 0.0f;
	currentImage.x = 0;
	attackCount = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime,bool faceRight, int type)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		
		if (type == 0) //PLAYER
		{
			if (currentImage.x >= 3 && row == 0) //IDLE
			{
				currentImage.x = 0;
			}
			if (currentImage.x >= 4 && row == 1) //WALKING
			{
				currentImage.x = 0;
			}
			if (currentImage.x >= 3 && row == 2) //L PUNCH
			{
				currentImage.x = 0;
				endAnimation = true;
				attackCount++;
			}
			if (currentImage.x >= 5 && row == 3) //R PUNCH
			{
				currentImage.x = 0;
				endAnimation = true;
				attackCount++;
			}
			if (currentImage.x >= 3 && row == 4) //KICK
			{
				currentImage.x = 0;
				endAnimation = true;
				attackCount = 0;
			}
			if (currentImage.x >= 4 && row == 7) //SP ATK
			{
				currentImage.x = 0;
				endAnimation = true;
			}
		}
		else if (type == 1) //GASTLER
		{
			if (currentImage.x >= 57 ) //IDLE
			{
				currentImage.x = 0;
			}
		}
		else if (type == 2) //HAUNTED
		{
			if (currentImage.x >= 14)
			{
				currentImage.x = 0;
			}
		}
		else if (type == 3) //GANGER
		{
			if (currentImage.x >= 20)
			{
				currentImage.x = 0;
			}
			/*else if (currentImage.y == 12)
			{
				row = 0;
			}*/
		}
	}
	uvRect.top = currentImage.y * uvRect.height;
	
	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
