#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Animation.h"
#include "Collider.h"
#include "Player.h"

class Projectile : public Entity
{
public:
	Projectile(int a);
	~Projectile();
	int atkDamage = 10;
	int spDamge = 30;
	int counter = 0;
	int directionPrj = 2; // 1 Left , 2 Right
	void Update(Vector2f playerPos, int a, int i);
	RectangleShape body;
	Clock timer;
	Collider GetCollider() { return Collider(body); }
};

