#include "Player.h"

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed, float sp) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->sp = sp;
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

	punch.setSize(sf::Vector2f(80.0f, 45.0f));
	punch.setOrigin(punch.getSize() / 2.0f);
	punch.setFillColor(Color::White);
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
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		movement.x += speed * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		movement.y -= speed * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		movement.y += speed * deltaTime;
	}
	if (sp < 2)
	{
		animation.currentImage.x = 0;
		row = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::LShift) && !isShoot && sp >= 2) // SP ATK
	{
		isShoot = true;
		animation.currentImage.x = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Space) && !isAttack) // NRM ATK
	{
		isAttack = true;
		animation.currentImage.x = 0;
	}
	

	if (isShoot)
	{
		row = 7;
	}
	else if (isAttack)
	{
		row = animation.attackCount + 2;
	}
	else if (movement.x == 0.0f && movement.y == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			faceRight = true;
			directionPrj = 2;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			faceRight = false;
			directionPrj = 1;
		}
	}
	if (faceRight)
	{
		punch.setPosition(body.getPosition().x + 27.0f, body.getPosition().y - 50.0f);
	}
	else
	{
		punch.setPosition(body.getPosition().x - 27.0f, body.getPosition().y - 50.0f);
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
		isDead = false;
		animation.endAnimation = false;
	}
	
	hitbody.setPosition(body.getPosition());
	animation.Update(row, deltaTime, faceRight, 0);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	hitbody.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	//window.draw(hitbody);
	//window.draw(punch);
	window.draw(body);
}