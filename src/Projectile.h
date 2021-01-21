#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Animation.h"
#include "Collider.h"
#include "Player.h"

class Projectile : public Entity
{
public:
	int atkDamage = 10;
	int spDamge = 30;
	int directionPrj = 2; // 1 Left , 2 Right
	void Update(sf::Vector2f playerPos);
	int countBullet = 0;
	Projectile();
	~Projectile();
	sf::RectangleShape body;
	Collider GetCollider() { return Collider(body); }
};

