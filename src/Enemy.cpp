#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int i, int ePosy, int a) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	// Gastler
	if (a == 1)
	{
		body.setSize(Vector2f(133.45f, 117.3f));
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition(1450.0f, ePosy);
		body.setTexture(texture);
		hitbody.setSize(Vector2f(90.0f, 100.0f));
		hitbody.setOrigin(hitbody.getSize() / 2.0f);
		hitbody.setPosition(body.getPosition());
		hitbody.setFillColor(Color::Red);
		eHP = 30;
	}
	// Haunted
	if (a == 2)
	{
		body.setSize(Vector2f(154.7f, 134.3f));
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition(1450.0f, ePosy);
		body.setTexture(texture);
		hitbody.setSize(Vector2f(100.0f, 100.0f));
		hitbody.setOrigin(hitbody.getSize() / 2.0f);
		hitbody.setPosition(body.getPosition());
		hitbody.setFillColor(Color::Blue);
		eHP = 70;
	}
	// Gangar
	if (a == 3)
	{
		body.setSize(Vector2f(125.0f, 123.25f));
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition(1450.0f, ePosy);
		body.setTexture(texture);
		hitbody.setSize(Vector2f(100.0f, 100.0f));
		hitbody.setOrigin(hitbody.getSize() / 2.0f);
		hitbody.setPosition(body.getPosition());
		hitbody.setFillColor(Color::Yellow);
		eHP = 100;
	}
}


Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime, int type)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (state == 1)
	{
		movement.x -= 20 * deltaTime;
	}
	animation.Update(row, deltaTime, faceRight, type);
	body.setTextureRect(animation.uvRect);
	hitbody.move(movement);
	body.move(movement);
}

void Enemy::Draw(RenderWindow& window)
{
	window.draw(hitbody);
	window.draw(body);
}