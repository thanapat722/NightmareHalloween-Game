#pragma once

int main()
{
	//Variables
	float darkraiMoveSpeed = 0.3;
	float enemyMoveSpeed = 0.3;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Test!", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::RectangleShape bg, darkrai;
	sf::Texture bgTexture, darkraiTexture;

	window.setSize(sf::Vector2u(1000, 800));

	// Map
	bgTexture.loadFromFile("photo/pvz/nightyard.jpg");
	bg.setSize(sf::Vector2f(1400.0f, 600.0f));
	bg.setPosition(0.0f, 0.0f);
	bg.setTexture(&bgTexture);

	// Player Sprite
	sf::Texture playerTexture;
	playerTexture.loadFromFile("photo/mobs/kenf.png");
	//player.setOrigin(player.getSize() / 2.0f);

	Player player(&playerTexture, sf::Vector2u(12, 12), 0.16f, 180.0f);

	Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 500.0f));
	Platform platform2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f));

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}

		player.Update(deltaTime);

		platform1.GetCollider().CheckCollision(player.GetCollider(), 0.0f);
		platform2.GetCollider().CheckCollision(player.GetCollider(), 0.0f);

		view.setCenter(player.GetPosition());

		window.clear();
		window.setView(view);
		window.draw(bg);
		player.Draw(window);
		platform1.Draw(window);
		platform2.Draw(window);
		window.display();
	}

	return 0;
}
