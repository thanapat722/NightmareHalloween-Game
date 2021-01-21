#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Entity.h"
#include "RDN.h"
#include <stdio.h>
class Enemy: public Entity
{
public:
	Enemy(Texture* texture, Vector2u imageCount, float switchTime, float speed, int i, float ePosy, float ePosx, int a);
	~Enemy();
	int directionPrj = 2; // 1 Left , 2 Right
	int state = 9, eHP;
	bool bossHit = false;
	void Update(float deltaTime, int type);
	void Draw(RenderWindow& window);

	Vector2f getPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(hitbody); }
	bool faceRight, isShoot;
	sf::RectangleShape body, hitbody;
	
private:
	Animation animation;
	unsigned int row;
	float speed;
	int type;
};

