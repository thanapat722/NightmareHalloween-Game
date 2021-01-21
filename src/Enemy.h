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
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int i, int ePosy, int a);
	~Enemy();
	int directionPrj = 2; // 1 Left , 2 Right
	int state, eHP;
	void Update(float deltaTime, int type);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(hitbody); }
	bool faceRight, isShoot;
	sf::RectangleShape body, hitbody;
	
private:
	Animation animation;
	unsigned int row;
	float speed;
	int type;
};

