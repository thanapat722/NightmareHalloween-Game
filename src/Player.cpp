#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(136.0f, 136.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(700.0f, 300.0f);
	body.setTexture(texture);

	hitbody.setSize(sf::Vector2f(55.0f, 136.0f));
	hitbody.setOrigin(hitbody.getSize() / 2.0f);
	hitbody.setPosition(body.getPosition());
	hitbody.setFillColor(Color::Green);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	Vector2f movement(0.0f, 0.0f);
	int mousePress = 0;

	if (Keyboard::isKeyPressed(Keyboard::Home)) //WARP
		body.setPosition(700.0f, 300.0f);
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		movement.x -= speed * deltaTime;
		directionPrj = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		movement.x += speed * deltaTime;
		directionPrj = 2;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		movement.y -= speed * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		movement.y += speed * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::LShift) && !isShoot) // SP ATK
	{
		isShoot = true;
		printf("US\n");
		animation.currentImage.x = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Space) && !isAttack) // NRM ATK
	{
		isAttack = true;
		printf("TH\n");
		animation.currentImage.x = 0;
	}

	if (isShoot)
	{
		row = 7;
		printf("SHOOT\n");
	}
	else if (isAttack)
	{
		row = animation.attackCount + 2;
		printf("ATK\n");
	}
	else if (movement.x == 0.0f && movement.y == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;

		if (movement.x > 0.0f) 
		{
			faceRight = true;
		}
		else if (faceRight == true && movement.y != 0)
			faceRight = true;
		else
			faceRight = false;
	}
	
	if (isShoot && animation.endAnimation)
	{
		isShoot = false;
		animation.endAnimation = false;
	}
	if (isAttack && animation.endAnimation)
	{
		isAttack = false;
		animation.endAnimation = false;
	}
	if (isDead && animation.endAnimation)
	{
		isAttack = false;
		animation.endAnimation = false;
	}
	

	animation.Update(row, deltaTime, faceRight, 0);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	hitbody.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(hitbody);
	window.draw(body);
}