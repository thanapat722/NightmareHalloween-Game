#include "Projectile.h"

Projectile::Projectile()
{
	
	body.setSize(sf::Vector2f(10.0f, 10.0f));
	body.setPosition(0.0f, 0.0f);
	body.setOrigin(55, 55);
	sprite.setOrigin(40, 40);
	sprite.setTextureRect(IntRect(0, 640, 80, 80));
	sprite.setScale(1.2f, 1.2f);
}

Projectile::~Projectile()
{
}

void Projectile::Update(sf::Vector2f playerPos)
{
	sprite.setPosition(body.getPosition());

	if (directionPrj == 1) //Left
	{
		int i = 0;
		sprite.setRotation(180);
		body.move(-7, 0);
		if (i <= 80)
		{
			sprite.setTextureRect(IntRect(i, 640, 80, 80));
			i += 80;
		}
		
	}
	if (directionPrj == 2) //Right
	{
		int i = 0;
		body.move(7, 0);
		if (i <= 80)
		{
			sprite.setTextureRect(IntRect(i, 640, 80, 80));
			i += 80;
		}
	}

}