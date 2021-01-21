#include "Projectile.h"

Projectile::Projectile(int a)
{
	if (a != 4)
	{
		body.setSize(Vector2f(10.0f, 10.0f));
		body.setPosition(0.0f, 0.0f);
		body.setOrigin(55, 55);
		sprite.setOrigin(40, 40);
		sprite.setTextureRect(IntRect(0, 640, 79, 79));
		sprite.setScale(1.2f, 1.2f);
	}
	else
	{
		body.setSize(Vector2f(10.0f, 10.0f));
		body.setPosition(0.0f, 0.0f);
		body.setOrigin(55, 55);
		sprite.setOrigin(40, 40);
		sprite.setTextureRect(IntRect(0, 720, 79, 79));
		sprite.setScale(1.7f, 1.7f);
	}

}

Projectile::~Projectile()
{
}

void Projectile::Update(Vector2f playerPos, int a, int i)
{
	sprite.setPosition(body.getPosition());
	if (a == 1)
	{
		if (directionPrj == 1) //Left
		{
			sprite.setRotation(180);
			body.move(-8, 0);
			sprite.setTextureRect(IntRect(i * 80, 640, 80, 80));
		}
		if (directionPrj == 2) //Right
		{
			body.move(8, 0);
			sprite.setTextureRect(IntRect(i * 80, 640, 80, 80));
		}
	}
	if (a == 4)
	{
		directionPrj = 1;
		if (directionPrj == 1) //Left
		{
			sprite.setRotation(180);
			body.move(-7, 0);
			sprite.setTextureRect(IntRect(i * 80, 720, 80, 80));
		}
		if (directionPrj == 2) //Right
		{
			body.move(7, 0);
			sprite.setTextureRect(IntRect(i * 80, 720, 80, 80));
		}
	}
}