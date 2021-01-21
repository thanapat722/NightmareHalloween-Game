#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Entity.h"
class Player: public Entity
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();
	int atkDamage = 10;
	int spDamge = 30;
	int directionPrj = 2; // 1 Left , 2 Right
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	
	sf::Vector2f getPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	Collider GetColliders() { return Collider(hitbody); }
	bool faceRight, isShoot = false, isAttack = false, isDead = false;
	Animation animation;
	sf::RectangleShape body, hitbody;

private:
	
	unsigned int row;
	float speed;
	
};

