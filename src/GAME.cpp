//SFML 2.5.2
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "Collider.h"
#include "Platform.h"
#include "Entity.h"
#include "Projectile.h"
#include <iostream> 
#include <vector> 
#include <time.h>
#include <Windows.h>
#include "Collision.h"
#include <fstream>
#include <string>

using namespace std;
using namespace sf;
using namespace Collision;
static const float VIEW_HEIGHT = 600.0f;
int score = 0;
void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	//Variables
	float deltaTime = 0.0f;
	int mode = 0;
	float Posx = 0;
	float Posy = 0;
	int counter = 0;
	int counter2 = 0;
	int counter3 = 0;
	int hp = 1000;
	int ePosy;
	bool isHover = false;
	srand((unsigned int)time(NULL));

	//View
	//View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	View view(Vector2f(0.0f, 0.0f), Vector2f(1120.0f, 600.00f));

	//Window
	RenderWindow window(VideoMode(1500, 800), "Nightmare Halloween", Style::Default);
	Image icon;
	icon.loadFromFile("photo/icon3.png");
	window.setIcon(500, 500, icon.getPixelsPtr());
	RectangleShape bg, darkrai;
	Texture bgTexture, darkraiTexture;
	window.setFramerateLimit(60);

	//Cursor
	Cursor cursor;

	//Button SoundFx
	SoundBuffer buttonPressedBuffer;
	buttonPressedBuffer.loadFromFile("SFX/SFX_1up01.ogg");
	Sound buttonPressedSound;
	buttonPressedSound.setVolume(30.0f);
	buttonPressedSound.setBuffer(buttonPressedBuffer);
	buttonPressedSound.setLoop(false);

	//Die SoundFx


	//Menu Music
	SoundBuffer menuSongBuffer;
	menuSongBuffer.loadFromFile("sounds/mainmenu.ogg");
	Sound menuSongSound;
	menuSongSound.setBuffer(menuSongBuffer);
	menuSongSound.setVolume(75.0f);
	menuSongSound.setLoop(true);

	//Menu Background
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("photo/menu/menu.png");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

	//Menu Button
	Texture mode0, mode1, mode2, mode3;
	mode0.loadFromFile("photo/menu/mode0.png");
	mode1.loadFromFile("photo/menu/mode1.png");
	mode2.loadFromFile("photo/menu/mode2.png");
	mode3.loadFromFile("photo/menu/mode3.png");
	Sprite smode0, smode1, smode2, smode3;
	smode0.setTexture(mode0);
	smode1.setTexture(mode1);
	smode2.setTexture(mode2);
	smode3.setTexture(mode3);
	smode0.setPosition(sf::Vector2f(0, 0));
	smode1.setPosition(sf::Vector2f(0, 0));
	smode2.setPosition(sf::Vector2f(0, 0));
	smode3.setPosition(sf::Vector2f(0, 0));

	//Scoreboard Background
	Texture sbackgroundTexture;
	sbackgroundTexture.loadFromFile("photo/menu/score.png");
	Sprite sbackgroundSprite;
	sbackgroundSprite.setTexture(sbackgroundTexture);

	//Scoreboard Music
	SoundBuffer scoreSongBuffer;
	scoreSongBuffer.loadFromFile("sounds/pre.ogg");
	Sound scoreSongSound;
	scoreSongSound.setBuffer(scoreSongBuffer);
	scoreSongSound.setVolume(50.0f);
	scoreSongSound.setLoop(true);

	//Scoreboard Button
	Texture back0, back1;
	back0.loadFromFile("photo/menu/back0.png");
	back1.loadFromFile("photo/menu/back1.png");
	Sprite sback0, sback1;
	sback0.setTexture(back0);
	sback1.setTexture(back1);
	sback0.setPosition(sf::Vector2f(0, 0));
	sback1.setPosition(sf::Vector2f(0, 0));

	//Preset
	Vector2i mouse;
	Vector2f centerView;
	Clock clock, clock2, timer, timer2, timer3, timerLose;

	//Fonts
	Font font1, font2, font3;
	if (!font1.loadFromFile("fonts/Minecraftia.ttf"))return EXIT_FAILURE;
	if (!font2.loadFromFile("fonts/DB.ttf"))return EXIT_FAILURE;
	if (!font3.loadFromFile("fonts/SF.otf"))return EXIT_FAILURE;

	//Text
	Text text;
	text.setFont(font3);
	text.setFillColor(Color::White);
	text.setString("Created By Thanapat Danpattanachaikul(61011387)");
	text.setCharacterSize(16);
	text.setOutlineThickness(1);
	text.setOutlineColor(Color::Black);
	text.setStyle(Text::Regular);
	Text lose;
	lose.setFont(font1);
	lose.setFillColor(Color::Red);
	lose.setString("YOU LOSE!");
	lose.setCharacterSize(72);
	lose.setOutlineThickness(1);
	lose.setOutlineColor(Color::Black);
	lose.setStyle(Text::Regular);

	//Music
	Music music;
	if (!music.openFromFile("sounds/night.ogg"))return EXIT_FAILURE;
	music.setVolume(40);
	music.setLoop(true);

	//HP Bar
	Texture HPtexture;
	RectangleShape HP(Vector2f(hp / 3.2f, 25.0f));
	if (!HPtexture.loadFromFile("photo/mobs/hpsprite_green.png"))return EXIT_FAILURE;
	HP.setTexture(&HPtexture);

	//HP Sprite
	Sprite hpbar;
	Texture HPbar;
	if (!HPbar.loadFromFile("photo/mobs/hpbar1.png"))return EXIT_FAILURE;
	hpbar.setScale(0.5, 0.5);
	hpbar.setTexture(HPbar);

	//Map
	if (!bgTexture.loadFromFile("photo/pvz/night.jpg"))return EXIT_FAILURE;
	bg.setSize(Vector2f(1400.0f, 600.0f));
	bg.setPosition(0.0f, 0.0f);
	bg.setTexture(&bgTexture);

	//Player Sprite
	Texture playerTexture;
	if (!playerTexture.loadFromFile("photo/mobs/kenf.png"))return EXIT_FAILURE;
	Player player(&playerTexture, Vector2u(12, 12), 0.15f, 280.0f);

	//Enemy Sprite
	Texture gastlerTexture, hauntedTexture, gangarTexture;
	if (!gastlerTexture.loadFromFile("photo/mobs/gastler.png"))return EXIT_FAILURE;
	if (!hauntedTexture.loadFromFile("photo/mobs/haunted.png"))return EXIT_FAILURE;
	if (!gangarTexture.loadFromFile("photo/mobs/gangar.png"))return EXIT_FAILURE;

	//Border
	Platform platformUp(nullptr, Vector2f(1400.0f, 0.0f), Vector2f(700.0f, 0.0f));
	Platform platformDown(nullptr, Vector2f(1400.0f, 0.0f), Vector2f(700.0f, 600.0f));
	Platform platformLeft(nullptr, Vector2f(0.0f, 600.0f), Vector2f(210.0f, 300.0f));
	Platform platformRight(nullptr, Vector2f(0.0f, 600.0f), Vector2f(1250.0f, 300.0f));

	//Projectile Vector Array
	vector<Projectile>::const_iterator iter;
	vector<Projectile> projectileArray;

	//Projectile Object
	class Projectile projectile1;
	Texture projectileTexture;
	projectileTexture.loadFromFile("photo/mobs/kenf.png");
	projectile1.sprite.setTexture(projectileTexture);

	//Spawn Gastler
	vector<Enemy> enemies1;
	for (int i = 0; i < 30; i++)
	{
		ePosy = ((rand() % 5) + 1) * 100 + 10;
		//printf("S %d\n", ePosy);
		enemies1.push_back(Enemy(&gastlerTexture, Vector2u(57, 1), 0.15f, 280.0f, i, ePosy, 1));
		Enemy& enemyArray = enemies1[i];
	}
	//Spawn Haunted
	vector<Enemy> enemies2;
	for (int i = 0; i < 15; i++)
	{
		ePosy = ((rand() % 5) + 1) * 100 + 10;
		//printf("H %d\n", ePosy);
		enemies2.push_back(Enemy(&hauntedTexture, Vector2u(14, 1), 0.15f, 280.0f, i, ePosy, 2));
		Enemy& enemyArray = enemies2[i];
	}
	//Spawn Ganger
	vector<Enemy> enemies3;
	for (int i = 0; i < 7; i++)
	{
		ePosy = ((rand() % 5) + 1) * 100 + 10;
		//printf("G %d\n", ePosy);
		enemies3.push_back(Enemy(&gangarTexture, Vector2u(20, 1), 0.15f, 280.0f, i, ePosy, 3));
		Enemy& enemyArray = enemies3[i];
	}

	while (window.isOpen())
	{
		//Main Menu Loop
		if (mode == 0)
			menuSongSound.play();
		else if (mode == 1)
			music.play();
		while (mode == 0)
		{
			mouse = Mouse::getPosition(window);
			Event menuEvent;
			view.setCenter(700.0f, 300.0f);

			//Game Clock Reset
			clock2.restart().asSeconds();
			deltaTime = clock.restart().asSeconds();

			while (window.pollEvent(menuEvent))
			{
				switch (menuEvent.type)
				{
				case Event::Closed:
					menuSongSound.stop();
					window.close();
					exit(0);
					break;
				case Event::MouseButtonPressed:
					if (menuEvent.mouseButton.button == Mouse::Left)
					{
						if (mouse.x > 704 && mouse.x < 801 && mouse.y > 379 && mouse.y < 421)
						{
							menuSongSound.stop();
							buttonPressedSound.play();
							player.body.setPosition(700.0f, 300.0f);
							player.hitbody.setPosition(700.0f, 300.0f);
							mode = 1;  // Play
						}
						else if (mouse.x > 618 && mouse.x < 886 && mouse.y > 457 && mouse.y < 494)
						{
							menuSongSound.stop();
							buttonPressedSound.play();
							mode = 2; // Scoreboard
						}
						else if (mouse.x > 708 && mouse.x < 796 && mouse.y > 529 && mouse.y < 565)
						{
							buttonPressedSound.play();
							menuSongSound.stop();
							//mode = 3; // Exit
							window.close();
							exit(0);
						}
					}
				case Event::Resized:
					ResizeView(window, view);
					break;
				}
			}
			window.draw(backgroundSprite);
			if (mouse.x > 704 && mouse.x < 801 && mouse.y > 379 && mouse.y < 421)
			{
				cursor.loadFromSystem(sf::Cursor::Hand);
				window.draw(smode1);
			}
			else if (mouse.x > 618 && mouse.x < 886 && mouse.y > 457 && mouse.y < 494)
			{
				cursor.loadFromSystem(sf::Cursor::Hand);
				window.draw(smode2);

			}
			else if (mouse.x > 708 && mouse.x < 796 && mouse.y > 529 && mouse.y < 565)
			{
				cursor.loadFromSystem(sf::Cursor::Hand);
				window.draw(smode3);
			}
			else
			{
				cursor.loadFromSystem(sf::Cursor::Arrow);
				window.draw(smode0);
			}

			window.setMouseCursor(cursor);
			window.setView(view);
			window.display();
			window.clear();
			//printf("mX = %d ", mouse.x);
			//printf("mY = %d \n", mouse.y);
		}

		//Scoreboard Loop
		if (mode == 2)
			scoreSongSound.play();
		else if (mode == 1)
			music.play();
		while (mode == 2)
		{
			mouse = Mouse::getPosition(window);
			Event scoreEvent;
			view.setCenter(700.0f, 300.0f);

			//Game Clock Reset
			clock2.restart().asSeconds();
			deltaTime = clock.restart().asSeconds();

			while (window.pollEvent(scoreEvent))
			{
				switch (scoreEvent.type)
				{
				case Event::Closed:
					scoreSongSound.stop();
					window.close();
					exit(0);
					break;
				case Event::MouseButtonPressed:
					if (scoreEvent.mouseButton.button == Mouse::Left)
					{
						if ((mouse.x > 870 && mouse.x < 1156 && mouse.y > 684 && mouse.y < 723))
						{
							buttonPressedSound.play();
							scoreSongSound.stop();
							mode = 0;  // Main Menu
						}
					}
				}
			}
			window.draw(sbackgroundSprite);
			if (mouse.x > 870 && mouse.x < 1156 && mouse.y > 684 && mouse.y < 723)
			{
				cursor.loadFromSystem(sf::Cursor::Hand);
				window.draw(sback1);
			}
			else
			{
				cursor.loadFromSystem(sf::Cursor::Arrow);
				window.draw(sback0);
			}

			window.setMouseCursor(cursor);
			window.setView(view);
			window.display();
			window.clear();
			//printf("mX = %d ", mouse.x);
			//printf("mY = %d \n", mouse.y);
		}

		//Game Loop
		while (mode == 1)
		{
			deltaTime = clock.restart().asSeconds();
			Event event;

			if (hp > 700)
			{
				if (!HPtexture.loadFromFile("photo/mobs/hpsprite_green.png"))return EXIT_FAILURE;
			}
			else if (hp > 300)
			{
				if (!HPtexture.loadFromFile("photo/mobs/hpsprite_yellow.png"))return EXIT_FAILURE;
			}
			else
			{
				if (!HPtexture.loadFromFile("photo/mobs/hpsprite_red.png"))return EXIT_FAILURE;
			}
			centerView = view.getCenter();
			Posx = view.getCenter().x;
			Posy = view.getCenter().y;

			printf("%d\n", score);

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
					window.close();
					music.stop();
					exit(0);
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == Keyboard::Escape)
					{
						music.stop();
						buttonPressedSound.play();
						mode = 0;  // Main Menu
					}
				case Event::Resized:
					ResizeView(window, view);
					break;
				}
			}

			player.Update(deltaTime);

			platformUp.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false);
			platformDown.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false);
			platformLeft.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false);
			platformRight.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false);

			if (player.getPosition().x >= 600 && player.getPosition().x <= 800)
			{
				view.setCenter(player.getPosition().x, 300);
			}

			player.hitbody.setPosition(player.body.getPosition());
			HP.setPosition(Vector2f(view.getCenter().x - 480, 35));
			hpbar.setPosition(view.getCenter().x - 500, 0);
			text.setPosition(centerView.x - 190, 580);
			lose.setPosition(centerView.x - 200, 250);
			window.clear();
			window.draw(bg);
			player.Draw(window);
			window.draw(text);

			//If Die
			if (hp <= 0) player.isDead = true;
			if (player.isDead)
			{
				timerLose.restart().asSeconds();
				do
				{
					window.clear();
					window.draw(lose);
					window.display();
					printf("LOSE!\n");
				} while (timerLose.getElapsedTime().asSeconds() <= 3 && hp <= 0);
				music.stop();
				mode = 0;
				hp = 1000;
				player.isDead = false;
				window.close();
				main();
			}

			//Special Attack
			if (Keyboard::isKeyPressed(Keyboard::LShift) && player.animation.currentImage.x == 2 && player.animation.currentImage.y == 7)
			{
				{
					if (counter3 != 0) counter3--;
					else
					{
						if (player.faceRight)
							projectile1.body.setPosition(player.getPosition().x + 50, player.getPosition().y - 20);
						else
							projectile1.body.setPosition(player.getPosition().x - 50, player.getPosition().y - 20);
						projectile1.directionPrj = player.directionPrj;
						projectileArray.push_back(projectile1);
						counter3 = 8;
					}
				}
			}
			window.setView(view);

			//Gastler Spawn
			if (clock2.getElapsedTime().asSeconds() >= 5)
			{
				for (unsigned int i = 0; i < enemies1.size(); i++)
				{
					if (timer.getElapsedTime().asSeconds() >= ((rand() % 7) + 2) && enemies1[i].state != 1)
					{
						enemies1[i].state = 1;
						timer.restart().asSeconds();
					}
					if(enemies1[i].eHP > 0)
						enemies1[i].Draw(window);
					enemies1[i].Update(deltaTime, 1);
				}
			}

			//Haunted Spawn
			if (clock2.getElapsedTime().asSeconds() >= 50)
			{
				for (unsigned int i = 0; i < enemies2.size(); i++)
				{
					if (timer2.getElapsedTime().asSeconds() >= ((rand() % 9) + 8) && enemies2[i].state != 1)
					{
						enemies2[i].state = 1;
						timer2.restart().asSeconds();
					}
					if (enemies2[i].eHP > 0)
						enemies2[i].Draw(window);
					enemies2[i].Update(deltaTime, 2);
				}
			}

			//Gangar Spawn
			if (clock2.getElapsedTime().asSeconds() >= 100)
			{
				for (unsigned int i = 0; i < enemies3.size(); i++)
				{
					if (timer3.getElapsedTime().asSeconds() >= ((rand() % 11) + 16) && enemies3[i].state != 1)
					{
						enemies3[i].state = 1;
						timer3.restart().asSeconds();
					}
					if (enemies3[i].eHP > 0)
						enemies3[i].Draw(window);
					enemies3[i].Update(deltaTime, 3);
				}
			}

			//Draw Projectile
			counter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				projectileArray[counter].Update(player.getPosition());
				window.draw(projectileArray[counter].sprite);
				counter++;
			}

			//Check Collision Player-Projectile-Ememy1
			for (unsigned int i = 0; i < enemies1.size(); i++)
			{
				if (enemies1[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, true))
				{
					printf("ชน\n");
					//enemies1[i].state = 0;
					if (hp > 0) hp--;
				}
				for (unsigned int j = 0; j < projectileArray.size(); j++)
				{
					if (enemies1[i].GetCollider().CheckCollision(projectileArray[j].GetCollider(), 0.0f, false) && enemies1[i].eHP > 0)
					{
						enemies1[i].eHP -= 20;
						score += 150;
					}	
				}
			}
			//Check Collision Player-Projectile-Ememy2
			for (unsigned int i = 0; i < enemies2.size(); i++)
			{
				if (enemies2[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, true))
				{
					printf("ชน\n");
					//enemies1[i].state = 0;
					if (hp > 0) hp--;
				}
				for (unsigned int j = 0; j < projectileArray.size(); j++)
				{
					if (enemies2[i].GetCollider().CheckCollision(projectileArray[j].GetCollider(), 0.0f, false) && enemies2[i].eHP > 0)
					{
						enemies2[i].eHP -= 20;
						projectileArray[j].body.setPosition(1500.0f, 0.0f);
						score += 300;
					}
				}
			}
			//Check Collision Player-Projectile-Ememy3
			for (unsigned int i = 0; i < enemies3.size(); i++)
			{
				if (enemies3[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, true))
				{
					printf("ชน\n");
					//enemies1[i].state = 0;
					if (hp > 0) hp--;
				}
				for (unsigned int j = 0; j < projectileArray.size(); j++)
				{
					if (enemies3[i].GetCollider().CheckCollision(projectileArray[j].GetCollider(), 0.0f, false) && enemies3[i].eHP > 0)
					{
						enemies3[i].eHP -= 20;
						score += 600;
					}
				}
			}

			//printf("%f\n", clock2.getElapsedTime().asSeconds());
			//HP Cheat
			if (Keyboard::isKeyPressed(Keyboard::Subtract) && hp > 0) hp -= 10;
			if (Keyboard::isKeyPressed(Keyboard::Add) && hp < 1000) hp += 10;
			
			HP.setSize(Vector2f(hp / 3.20f, 21.0f));
			cursor.loadFromSystem(sf::Cursor::Arrow);
			window.setMouseCursor(cursor);
			window.draw(hpbar);
			window.draw(HP);
			platformUp.Draw(window);
			platformDown.Draw(window);
			platformLeft.Draw(window);
			platformRight.Draw(window);
			window.display();
		}
	}
	return 0;
}