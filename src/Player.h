#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Entity.h"
class Player: public Entity
{
public:
	Player(Texture* texture, Vector2u imageCount, float switchTime, float speed, float sp);
	~Player();
	int directionPrj = 2; // 1 Left , 2 Right
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	
	Vector2f getPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	Collider GetColliders() { return Collider(hitbody); }
	Collider GetColliderP() { return Collider(punch); }
	bool faceRight, isShoot = false, isAttack = false, isDead = false;
	float sp;
	Animation animation;
	RectangleShape body, hitbody, punch;

private:
	
	unsigned int row;
	float speed;
};

