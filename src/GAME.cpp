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
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;
using namespace sf;
static const float VIEW_HEIGHT = 600.0f;
void ResizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	//Variables
	float deltaTime = 0.0f;
	int Dmg = 10;
	int spDmg = 20;
	int Score = 0;
	int mode = 0;
	int spawnState = 0;
	float Posx = 9000;
	float Posy = 9000;
	int counter = 0;
	int counter2 = 0;
	int counter3 = 0;
	int counter4 = 0;
	int counter5 = 0;
	int hp = 1000;
	float sp = 100;
	int lvl = 1;
	float ePosy = 0;
	bool isLose = false, isWin = false, isSetup = false, isPick = false, isGet = false;
	bool win1 = false, win2 = false, win3 = false, win4 = false, winCheck = true, Win = false;
	bool nameEntered = false;
	int splash = 1;
	int p = 0;
	int bossCheck = 0;
	int enemies1Spawn = 0, enemies2Spawn = 0, enemies3Spawn = 0, bossSpawn = 0;
	int enemies1Time = 0, enemies2Time = 0, enemies3Time = 0, bossTime = 0, itemTime2 = 0;
	int spawnTime1 = 0, spawnTime2 = 0, spawnTime3 = 0, spawnTime4 = 0;
	srand((unsigned int)time(NULL));
	string yourname;
	Text tplayer;

	vector<pair<int, string>> scoreboard;
	ifstream loadFile;
	loadFile.open("score.txt");
	while (!loadFile.eof()) {
		string tempName;
		int tempScore;
		loadFile >> tempName >> tempScore;
		scoreboard.push_back({ tempScore,tempName });
		sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, string>>());
	}
	

	//View
	//View view(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	View view(Vector2f(0.0f, 0.0f), Vector2f(1120.0f, 600.00f));

	//Window
	RenderWindow window(VideoMode(1500, 800), "Nightmare Halloween", Style::Close);
	Image icon;
	icon.loadFromFile("photo/icon3.png");
	window.setIcon(500, 500, icon.getPixelsPtr());
	RectangleShape bg;
	Texture bgTexture;
	window.setFramerateLimit(60);

	//Cursor
	Cursor cursor;

	//Button SoundFx
	SoundBuffer buttonPressedBuffer;
	buttonPressedBuffer.loadFromFile("SFX/SFX_1up01.ogg");
	Sound buttonPressedSound;
	buttonPressedSound.setVolume(30.0f);
	buttonPressedSound.setBuffer(buttonPressedBuffer);

	//SP ATK SoundFx
	SoundBuffer spatkBuffer;
	spatkBuffer.loadFromFile("SFX/vo/hadouken.wav");
	Sound spatkFX;
	spatkFX.setBuffer(spatkBuffer);
	spatkFX.setVolume(30.0f);

	SoundBuffer spatkHitBuffer;
	spatkHitBuffer.loadFromFile("SFX/SFX_Hit04.ogg");
	Sound spatkHitFX;
	spatkHitFX.setBuffer(spatkHitBuffer);
	spatkHitFX.setVolume(30.0f);
	
	//Hit SoundFx
	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("SFX/vo/hit1.wav");
	Sound hitFX;
	hitFX.setBuffer(hitBuffer);
	hitFX.setVolume(50.0f);

	//Win SoundFx
	SoundBuffer nextBuffer;
	nextBuffer.loadFromFile("SFX/20H.wav");
	Sound nextFX;
	nextFX.setBuffer(nextBuffer);
	nextFX.setVolume(30.0f);

	//Item SoundFx
	SoundBuffer itemBuffer;
	itemBuffer.loadFromFile("SFX/SFX_Coin01.ogg");
	Sound itemFX;
	itemFX.setBuffer(itemBuffer);
	itemFX.setVolume(40.0f);

	//Win SoundFx
	SoundBuffer winBuffer;
	winBuffer.loadFromFile("sounds/victory.ogg");
	Sound winFX;
	winFX.setBuffer(winBuffer);
	winFX.setVolume(30.0f);

	//Lose SoundFx
	SoundBuffer loseBuffer;
	loseBuffer.loadFromFile("SFX/vo/no.wav");
	Sound loseFX;
	loseFX.setBuffer(loseBuffer);
	loseFX.setVolume(30.0f);

	//Bite SoundFx
	SoundBuffer biteBuffer;
	biteBuffer.loadFromFile("SFX/vo/classic_hurt.wav");
	Sound biteFX;
	biteFX.setBuffer(biteBuffer);
	biteFX.setVolume(50.0f);

	//Out of Pow
	SoundBuffer outBuffer;
	outBuffer.loadFromFile("SFX/SFX_Boom02.ogg");
	Sound outFX;
	outFX.setBuffer(outBuffer);
	outFX.setVolume(50.0f);

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
	backgroundTexture.setSmooth(true);
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

	//Menu Button
	Texture mode0, mode1, mode2, mode3, mode4;
	mode0.loadFromFile("photo/menu/mode0.png");
	mode1.loadFromFile("photo/menu/mode1.png");
	mode2.loadFromFile("photo/menu/mode2.png");
	mode3.loadFromFile("photo/menu/mode3.png");
	mode4.loadFromFile("photo/menu/mode4.png");
	mode0.setSmooth(true);
	mode1.setSmooth(true);
	mode2.setSmooth(true);
	mode3.setSmooth(true);
	mode4.setSmooth(true);
	Sprite smode0, smode1, smode2, smode3, smode4;
	smode0.setTexture(mode0);
	smode1.setTexture(mode1);
	smode2.setTexture(mode2);
	smode3.setTexture(mode3);
	smode4.setTexture(mode4);
	smode0.setPosition(Vector2f(0, 0));
	smode1.setPosition(Vector2f(0, 0));
	smode2.setPosition(Vector2f(0, 0));
	smode3.setPosition(Vector2f(0, 0));
	smode4.setPosition(Vector2f(0, 0));

	//How to Background
	Texture howtoTexture;
	howtoTexture.loadFromFile("photo/menu/howto.png");
	howtoTexture.setSmooth(true);
	Sprite howtoSprite;
	howtoSprite.setTexture(howtoTexture);

	//Scoreboard Background
	Texture sbackgroundTexture;
	sbackgroundTexture.loadFromFile("photo/menu/score.png");
	sbackgroundTexture.setSmooth(true);
	Sprite sbackgroundSprite;
	sbackgroundSprite.setTexture(sbackgroundTexture);

	//Scoreboard Music
	SoundBuffer scoreSongBuffer;
	scoreSongBuffer.loadFromFile("sounds/rush.ogg");
	Sound scoreSongSound;
	scoreSongSound.setBuffer(scoreSongBuffer);
	scoreSongSound.setVolume(50.0f);
	scoreSongSound.setLoop(true);

	//How to Music
	SoundBuffer howtoBuffer;
	howtoBuffer.loadFromFile("sounds/pre.ogg");
	Sound howtoSound;
	howtoSound.setBuffer(howtoBuffer);
	howtoSound.setVolume(50.0f);
	howtoSound.setLoop(true);

	//Scoreboard Button
	Texture back0, back1;
	back0.loadFromFile("photo/menu/back0.png");
	back1.loadFromFile("photo/menu/back1.png");
	back0.setSmooth(true);
	back1.setSmooth(true);
	Sprite sback0, sback1;
	sback0.setTexture(back0);
	sback1.setTexture(back1);
	sback0.setPosition(Vector2f(0, 0));
	sback1.setPosition(Vector2f(0, 0));

	//End Game Backgorund
	Texture endTexture;
	endTexture.setSmooth(true);
	
	//End Game Music
	SoundBuffer endSongBuffer;
	endSongBuffer.loadFromFile("sounds/pre.ogg");
	Sound endSongSound;
	endSongSound.setBuffer(endSongBuffer);
	endSongSound.setVolume(30.0f);
	endSongSound.setLoop(true);

	//Preset
	Vector2i mouse;
	Vector2f centerView;
	Clock clock, clock2, timer, timer2, timer3, timer4, timerPrj, timerLose, dpsTimer, itemTime;

	//Fonts
	Font font1, font2, font3, font4;
	if (!font1.loadFromFile("fonts/Minecraftia.ttf"))return EXIT_FAILURE;
	if (!font2.loadFromFile("fonts/DB.ttf"))return EXIT_FAILURE;
	if (!font3.loadFromFile("fonts/SF.otf"))return EXIT_FAILURE;
	if (!font4.loadFromFile("fonts/Gloria.ttf"))return EXIT_FAILURE;

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
	Text score;
	score.setFont(font1);
	score.setCharacterSize(24);
	score.setOutlineThickness(1);
	score.setOutlineColor(Color::Black);
	score.setFillColor(sf::Color::White);
	score.setString("0");
	Text lvl1;
	lvl1.setFont(font1);
	lvl1.setFillColor(Color::White);
	lvl1.setString("D-3");
	lvl1.setCharacterSize(20);
	lvl1.setOutlineThickness(1);
	lvl1.setOutlineColor(Color::Black);
	lvl1.setStyle(Text::Regular);
	Text lvl2;
	lvl2.setFont(font1);
	lvl2.setFillColor(Color::White);
	lvl2.setString("D-2");
	lvl2.setCharacterSize(20);
	lvl2.setOutlineThickness(1);
	lvl2.setOutlineColor(Color::Black);
	lvl2.setStyle(Text::Regular);
	Text lvl3;
	lvl3.setFont(font1);
	lvl3.setFillColor(Color::White);
	lvl3.setString("D-1");
	lvl3.setCharacterSize(20);
	lvl3.setOutlineThickness(1);
	lvl3.setOutlineColor(Color::Black);
	lvl3.setStyle(Text::Regular);
	Text lvl4;
	lvl4.setFont(font1);
	lvl4.setFillColor(Color::White);
	lvl4.setString("D-Day");
	lvl4.setCharacterSize(20);
	lvl4.setOutlineThickness(1);
	lvl4.setOutlineColor(Color::Black);
	lvl4.setStyle(Text::Regular);

	//Music
	Music music;
	music.setVolume(50);
	music.setLoop(true);

	//HP Bar
	Texture HPtexture;
	RectangleShape HP(Vector2f(hp / 3.2f, 25.0f));
	if (!HPtexture.loadFromFile("photo/mobs/hpsprite_green.png"))return EXIT_FAILURE;
	HP.setTexture(&HPtexture);
	//SP Bar
	Texture SPtexture;
	RectangleShape SP(Vector2f(sp / 0.32f, 25.0f));
	if (!SPtexture.loadFromFile("photo/mobs/powsprite.png"))return EXIT_FAILURE;
	SP.setTexture(&SPtexture);

	//HP Sprite
	Sprite hpbar;
	Texture HPbar;
	if (!HPbar.loadFromFile("photo/mobs/hpbar3.png"))return EXIT_FAILURE;
	hpbar.setScale(0.5, 0.5);
	hpbar.setTexture(HPbar);

	//Map
	if (!bgTexture.loadFromFile("photo/pvz/night.jpg"))return EXIT_FAILURE;
	bgTexture.setSmooth(true);
	bgTexture.setSmooth(true);
	bg.setSize(Vector2f(1400.0f, 600.0f));
	bg.setPosition(0.0f, 0.0f);
	bg.setTexture(&bgTexture);

	//Player Sprite
	Texture playerTexture;
	if (!playerTexture.loadFromFile("photo/mobs/kenf.png"))return EXIT_FAILURE;
	Player player(&playerTexture, Vector2u(12, 12), 0.15f, 280.0f, sp);

	//Enemy Sprite
	Texture gastlerTexture, hauntedTexture, gangarTexture, darkriseTexture;
	if (!gastlerTexture.loadFromFile("photo/mobs/gastler.png"))return EXIT_FAILURE;
	if (!hauntedTexture.loadFromFile("photo/mobs/haunted.png"))return EXIT_FAILURE;
	if (!gangarTexture.loadFromFile("photo/mobs/gangar.png"))return EXIT_FAILURE;
	if (!darkriseTexture.loadFromFile("photo/mobs/darkrai.png"))return EXIT_FAILURE;
	gastlerTexture.setSmooth(true);
	hauntedTexture.setSmooth(true);
	gangarTexture.setSmooth(true);
	darkriseTexture.setSmooth(true);

	//Item Sprite
	Texture itemTexture;
	if (!itemTexture.loadFromFile("photo/item/potion.png"))return EXIT_FAILURE;
	itemTexture.setSmooth(true);

	//Level Plate
	Texture lv1Texture, lv2Texture, lv3Texture, lv4Texture;
	if (!lv1Texture.loadFromFile("photo/menu/n1.png"))return EXIT_FAILURE;
	if (!lv2Texture.loadFromFile("photo/menu/n2.png"))return EXIT_FAILURE;
	if (!lv3Texture.loadFromFile("photo/menu/n3.png"))return EXIT_FAILURE;
	if (!lv4Texture.loadFromFile("photo/menu/n4.png"))return EXIT_FAILURE;
	lv1Texture.setSmooth(true);
	lv2Texture.setSmooth(true);
	lv3Texture.setSmooth(true);
	lv4Texture.setSmooth(true);

	//Border
	Platform platformUp(nullptr, Vector2f(1400.0f, 0.0f), Vector2f(700.0f, 0.0f));
	Platform platformDown(nullptr, Vector2f(1400.0f, 0.0f), Vector2f(700.0f, 600.0f));
	Platform platformLeft(nullptr, Vector2f(0.0f, 600.0f), Vector2f(210.0f, 300.0f));
	Platform platformRight(nullptr, Vector2f(0.0f, 600.0f), Vector2f(1150.0f, 300.0f));
	Platform platformHouse(nullptr, Vector2f(0.0f, 600.0f), Vector2f(150.0f, 300.0f));
	Platform platformb1(nullptr, Vector2f(1400.0f, 0.0f), Vector2f(700.0f, 110.0f));
	Platform platformb2(nullptr, Vector2f(1400.0f, 0.0f), Vector2f(700.0f, 510.0f));

	//Projectile Vector Array
	vector<Projectile>::const_iterator iter;
	vector<Projectile> projectileArray, projectileArrayBoss;

	//Projectile Object
	class Projectile projectile1(1);
	Texture projectileTexture;
	projectileTexture.loadFromFile("photo/mobs/kenf.png");
	projectile1.sprite.setTexture(projectileTexture);

	//Projectile Object
	class Projectile projectile2(4);
	Texture projectile2Texture;
	projectile2Texture.loadFromFile("photo/mobs/kenf.png");
	projectile2.sprite.setTexture(projectile2Texture);

	//Enemies Vector
	vector<Enemy> enemies1, enemies2, enemies3, boss, item;

	while (window.isOpen())
	{
		//Main Menu Loop
		if (mode == 0)
		{
			score.setFont(font1);
			hp = 1000;
			Score = 0;
			spawnState = 0;
			win1 = false;
			win2 = false;
			win3 = false;
			win4 = false;
			Win = false;
			lvl = 1;
			splash = 1;
			isSetup = false;
			isGet = false;
			nameEntered = false;
			player.isDead = false;
			enemies1.clear();
			enemies2.clear();
			enemies3.clear();
			boss.clear();
			projectileArrayBoss.clear();
			yourname.clear();
			Posx = 9000;
			Posy = 9000;
			menuSongSound.play();
		}
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
						if (mouse.x > 695 && mouse.x < 810 && mouse.y > 319 && mouse.y < 373)
						{
							menuSongSound.stop();
							buttonPressedSound.play();
							player.body.setPosition(700.0f, 300.0f);
							player.hitbody.setPosition(700.0f, 300.0f);
							mode = 1;
						}
						else if (mouse.x > 593 && mouse.x < 908 && mouse.y > 417 && mouse.y < 468)
						{
							menuSongSound.stop();
							buttonPressedSound.play();
							mode = 5;
						}
						else if (mouse.x > 590 && mouse.x < 904 && mouse.y > 510 && mouse.y < 553)
						{
							menuSongSound.stop();
							buttonPressedSound.play();
							mode = 2;
						}
						else if (mouse.x > 700 && mouse.x < 804 && mouse.y > 598 && mouse.y < 640)
						{
							buttonPressedSound.play();
							menuSongSound.stop();
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
			if (mouse.x > 695 && mouse.x < 810 && mouse.y > 319 && mouse.y < 373)
			{
				cursor.loadFromSystem(Cursor::Hand);
				window.draw(smode1);
			}
			else if (mouse.x > 593 && mouse.x < 908 && mouse.y > 417 && mouse.y < 468)
			{
				cursor.loadFromSystem(Cursor::Hand);
				window.draw(smode4);

			}
			else if (mouse.x > 590 && mouse.x < 904 && mouse.y > 510 && mouse.y < 553)
			{
				cursor.loadFromSystem(Cursor::Hand);
				window.draw(smode2);

			}
			else if (mouse.x > 700 && mouse.x < 804 && mouse.y > 598 && mouse.y < 640)
			{
				cursor.loadFromSystem(Cursor::Hand);
				window.draw(smode3);
			}
			else
			{
				cursor.loadFromSystem(Cursor::Arrow);
				window.draw(smode0);
			}

			window.setMouseCursor(cursor);
			window.setView(view);
			window.display();
			window.clear();
		}

		//Scoreboard Loop
		if (mode == 2)
		{
			scoreSongSound.play();
		}
		else if (mode == 1)
			music.play();
		while (mode == 2)
		{
			mouse = Mouse::getPosition(window);
			Event scoreEvent;
			view.setCenter(700.0f, 300.0f);
			back0.loadFromFile("photo/menu/back0.png");
			back1.loadFromFile("photo/menu/back1.png");

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
							mode = 0;
						}
					}
				}
			}
			window.clear();
			window.draw(sbackgroundSprite);
			if (mouse.x > 870 && mouse.x < 1156 && mouse.y > 684 && mouse.y < 723)
			{
				cursor.loadFromSystem(Cursor::Hand);
				window.draw(sback1);
			}
			else
			{
				cursor.loadFromSystem(Cursor::Arrow);
				window.draw(sback0);
			}
			int cnt = 0;
			for (vector<pair<int, string>>::iterator i = scoreboard.begin(); i != scoreboard.end(); ++i)
			{
				++cnt;
				if (cnt > 5) break;
				Text a, b;
				a.setString(to_string(i->first));
				a.setFont(font4);
				a.setFillColor(Color::Black);
				a.setCharacterSize(35);
				a.setPosition(775.0f , float(140 + (55 * cnt)));
				window.draw(a);
				b.setString(i->second);
				b.setFont(font4);
				b.setFillColor(Color::Black);
				b.setCharacterSize(35);
				b.setPosition(500.0f , float(140 + (55 * cnt)));
				window.draw(b);
			}
			window.setMouseCursor(cursor);
			window.setView(view);
			window.display();
		}

		//Game Loop
		while (mode == 1)
		{
			Event event;
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
			deltaTime = clock.restart().asSeconds();
			ostringstream sc;
			sc << Score;
			score.setString(sc.str());
			score.setCharacterSize(24);
			score.setOutlineThickness(1);
			score.setOutlineColor(Color::Black);
			score.setFillColor(Color::White);

			if (lvl == 1 && !isSetup)
			{
				spawnTime1 = 5; spawnTime2 = 25; spawnTime3 = 62;
				enemies1Spawn = 22;
				enemies2Spawn = 13;
				enemies3Spawn = 5;
				bossSpawn = 0; spawnTime4 = 0; bossTime = 0;
				clock2.restart().asSeconds();
				timer.restart();
				timer2.restart();
				timer3.restart();
				timer4.restart();
				itemTime.restart().asSeconds();
				isSetup = true;
			}
			else if (lvl == 2 && !isSetup)
			{
				spawnTime1 = 5; spawnTime2 = 18; spawnTime3 = 54;
				enemies1Spawn = 27;
				enemies2Spawn = 15;
				enemies3Spawn = 7;
				bossSpawn = 0; spawnTime4 = 0; bossTime = 0;
				clock2.restart().asSeconds();
				timer.restart();
				timer2.restart();
				timer3.restart();
				timer4.restart();
				itemTime.restart().asSeconds();
				isSetup = true;
			}
			else if (lvl == 3 && !isSetup)
			{
				spawnTime1 = 5; spawnTime2 = 10; spawnTime3 = 27;
				enemies1Spawn = 33;
				enemies2Spawn = 22;
				enemies3Spawn = 11;
				bossSpawn = 0; spawnTime4 = 0; bossTime = 0;
				clock2.restart().asSeconds();
				timer.restart();
				timer2.restart();
				timer3.restart();
				timer4.restart();
				itemTime.restart().asSeconds();
				isSetup = true;
			}
			else if (lvl == 4 && !isSetup)
			{
				spawnTime1 = 0; spawnTime2 = 0; spawnTime3 = 0;
				enemies1Spawn = 0;
				enemies2Spawn = 0;
				enemies3Spawn = 0;
				bossSpawn = 1; spawnTime4 = 3; bossTime = 2;
				clock2.restart().asSeconds();
				timer.restart();
				timer2.restart();
				timer3.restart();
				timer4.restart();
				itemTime.restart().asSeconds();
				isSetup = true;
			}

			//Plate
			RectangleShape lv1, lv2, lv3, lv4;
			lv1.setTexture(&lv1Texture);
			lv2.setTexture(&lv2Texture);
			lv3.setTexture(&lv3Texture);
			lv4.setTexture(&lv4Texture);
			Sprite lv1Sprite, lv2Sprite, lv3Sprite, lv4Sprite;
			lv1Sprite.setTexture(lv1Texture); lv1Sprite.setOrigin(Vector2f(1500.0f, 800.0f) / 2.0f);
			lv2Sprite.setTexture(lv2Texture); lv2Sprite.setOrigin(Vector2f(1500.0f, 800.0f) / 2.0f);
			lv3Sprite.setTexture(lv3Texture); lv3Sprite.setOrigin(Vector2f(1500.0f, 800.0f) / 2.0f);
			lv4Sprite.setTexture(lv4Texture); lv4Sprite.setOrigin(Vector2f(1500.0f, 800.0f) / 2.0f);

			while (lvl == 1 && splash == 1)
			{
				if (!music.openFromFile("sounds/night.ogg"))return EXIT_FAILURE;
				lv1Sprite.setPosition(view.getCenter());
				nextFX.play();
				for (int i = 255; i >= 0; i--)
				{
					lv1Sprite.setColor(Color(255, 255, 255, i));
					window.clear();
					window.draw(lv1Sprite);
					window.display();
				}
				music.play();
				clock.restart().asSeconds();
				clock2.restart().asSeconds();
				itemTime.restart().asSeconds();
				timer.restart();
				timer2.restart();
				timer3.restart();
				timer4.restart();
				splash = 2;
				break;
			}
			while (lvl == 2 && splash == 2)
			{
				if (!music.openFromFile("sounds/lv2.ogg"))return EXIT_FAILURE;
				lv2Sprite.setPosition(view.getCenter());
				nextFX.play();
				for (int i = 255; i >= 0; i--)
				{
					lv2Sprite.setColor(Color(255, 255, 255, i));
					window.clear();
					window.draw(lv2Sprite);
					window.display();
				}
				music.play();
				clock.restart().asSeconds();
				clock2.restart().asSeconds();
				itemTime.restart().asSeconds();
				timer.restart();
				timer2.restart();
				timer3.restart();
				timer4.restart();
				splash = 3;
				break;
			}
			while (lvl == 3 && splash == 3)
			{
				if (!music.openFromFile("sounds/lv3.ogg"))return EXIT_FAILURE;
				lv3Sprite.setPosition(view.getCenter());
				nextFX.play();
				for (int i = 255; i >= 0; i--)
				{
					lv3Sprite.setColor(Color(255, 255, 255, i));
					window.clear();
					window.draw(lv3Sprite);
					window.display();
				}
				music.play();
				clock.restart().asSeconds();
				clock2.restart().asSeconds();
				itemTime.restart().asSeconds();
				timer.restart();
				timer2.restart();
				timer3.restart();
				timer4.restart();
				splash = 4;
				break;
			}
			while (lvl == 4 && splash == 4)
			{
				if (!music.openFromFile("sounds/boss.ogg"))return EXIT_FAILURE;
				lv4Sprite.setPosition(view.getCenter());
				nextFX.play();
				for (int i = 255; i >= 0; i--)
				{
					lv4Sprite.setColor(Color(255, 255, 255, i));
					window.clear();
					window.draw(lv4Sprite);
					window.display();
				}
				music.play();
				clock.restart().asSeconds();
				clock2.restart().asSeconds();
				itemTime.restart().asSeconds();
				timer.restart();
				timer2.restart();
				timer3.restart();
				timer4.restart();
				splash = 1;
				break;
			}

			//Spawn Enemy
			if (spawnState == 0)
			{
				for (int i = 0; i < enemies1Spawn; i++)
				{
					ePosy = float(((rand() % 5) + 1) * 100 + 10);
					enemies1.push_back(Enemy(&gastlerTexture, Vector2u(57, 1), 0.12f, 280.0f, i, ePosy, 1450.0f, 1));
					Enemy& enemyArray = enemies1[i];
				}
				for (int i = 0; i < enemies2Spawn; i++)
				{
					ePosy = float(((rand() % 5) + 1) * 100 + 10);
					enemies2.push_back(Enemy(&hauntedTexture, Vector2u(14, 1), 0.12f, 280.0f, i, ePosy, 1450.0f, 2));
					Enemy& enemyArray = enemies2[i];
				}
				for (int i = 0; i < enemies3Spawn; i++)
				{
					ePosy = float(((rand() % 5) + 1) * 100 + 10);
					enemies3.push_back(Enemy(&gangarTexture, Vector2u(20, 1), 0.12f, 280.0f, i, ePosy, 1450.0f, 3));
					Enemy& enemyArray = enemies3[i];
				}
				for (int i = 0; i < bossSpawn; i++)
				{
					ePosy = float(((rand() % 5) + 1) * 100 + 10);
					boss.push_back(Enemy(&darkriseTexture, Vector2u(35, 1), 0.1f, 280.0f, i, 310, 1100.0f, 4));
					Enemy& enemyArray = boss[i];
					boss[i].state = 2;
				}
				clock.restart().asSeconds();
				itemTime.restart().asSeconds();
				winCheck = false;
				spawnState = 1;
			}

			//Spawn Item
			if (clock2.getElapsedTime().asSeconds() >= 35)
			{
				if (itemTime.getElapsedTime().asSeconds() > itemTime2 && !isPick)
				{
					Posx = float(((rand() % 7) + 1) * 90 + 300);
					Posy = float(((rand() % 5) + 1) * 100 + 10);
					itemTime2 = rand() % 20 + 15;
					isPick = true;
				}
			}
			Platform platformPrj1(nullptr, Vector2f(0.0f, 500.0f), Vector2f(player.getPosition().x + 250, player.getPosition().y));
			Platform platformPrj2(nullptr, Vector2f(10.0f, 500.0f), Vector2f(player.getPosition().x - 250, player.getPosition().y));
			Platform items(&itemTexture, Vector2f(50.0f, 50.0f), Vector2f(Posx, Posy));

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

			player.Update(deltaTime);

			platformUp.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false);
			platformDown.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false);
			platformLeft.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false);
			platformRight.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false);

			if (player.getPosition().x >= 600 && player.getPosition().x <= 800)
			{
				view.setCenter(player.getPosition().x, 300);
			}

			window.clear();
			window.draw(bg);
			score.setPosition(centerView.x + 300, 16);
			HP.setPosition(Vector2f(view.getCenter().x - 469, 20));
			SP.setPosition(Vector2f(view.getCenter().x - 98, 20));
			hpbar.setPosition(view.getCenter().x - 500, -15);
			text.setPosition(centerView.x - 190, 578);
			lose.setPosition(centerView.x - 200, 250);
			lvl1.setPosition(centerView.x + 480, 18);
			lvl2.setPosition(centerView.x + 480, 18);
			lvl3.setPosition(centerView.x + 480, 18);
			lvl4.setPosition(centerView.x + 450, 18);
			player.Draw(window);
			window.draw(text);
			window.draw(score);
			if (lvl == 1)
				window.draw(lvl1);
			else if (lvl == 2)
				window.draw(lvl2);
			else if (lvl == 3)
				window.draw(lvl3);
			else if (lvl == 4)
				window.draw(lvl4);

			//If Win
			if (isWin)
			{
				spawnState = 0;
				hp = 1000;
				sp = 100;
				player.isDead = false;
				isSetup = false;
				isGet = false;
				clock2.restart().asSeconds();
				isWin = false;
				if (Win)
				{
					winFX.play();
					mode = 4;
				}
			}

			//If Die
			if (hp <= 0) player.isDead = true;
			if (player.isDead)
			{
				loseFX.play();
				music.stop();
				hp = 1000;
				sp = 100;
				spawnState = 0;
				enemies1.clear();
				enemies2.clear();
				enemies3.clear();
				boss.clear();
				isGet = false;
				isSetup = false;
				player.isDead = false;
				mode = 4;
				break;
			}

			//Special Attack
			if (player.animation.currentImage.x == 2 && player.animation.currentImage.y == 7 && sp >= 2)
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
						spatkFX.play();
						counter3 = 8;
					}
					sp -= 2;
					if (sp < 2) outFX.play();
				}
			}
			for (unsigned int i = 0; i < projectileArray.size(); i++)
			{
				if (platformPrj1.GetCollider().CheckCollision(projectileArray[i].GetCollider(), 1.0f, false) || platformPrj2.GetCollider().CheckCollision(projectileArray[i].GetCollider(), 1.0f, false))
				{
					projectileArray.erase(projectileArray.begin() + i);
				}
			}

			window.setView(view);

			//Gastler Spawn
			if (clock2.getElapsedTime().asSeconds() >= spawnTime1)
			{
				for (unsigned int i = 0; i < enemies1.size(); i++)
				{
					if (timer.getElapsedTime().asSeconds() >= enemies1Time && enemies1[i].state != 1)
					{
						enemies1[i].state = 1;
						timer.restart().asSeconds();
						enemies1Time = ((rand() % 5) + 3);
					}
					if (enemies1[i].eHP > 0)
						enemies1[i].Draw(window);
					enemies1[i].Update(deltaTime, 1);
				}
			}

			//Haunted Spawn
			if (clock2.getElapsedTime().asSeconds() >= spawnTime2)
			{
				for (unsigned int i = 0; i < enemies2.size(); i++)
				{
					if (timer2.getElapsedTime().asSeconds() >= enemies2Time && enemies2[i].state != 1)
					{
						enemies2[i].state = 1;
						timer2.restart().asSeconds();
						enemies2Time = ((rand() % 7) + 4);
					}
					if (enemies2[i].eHP > 0)
						enemies2[i].Draw(window);
					enemies2[i].Update(deltaTime, 2);
				}
			}

			//Gangar Spawn
			if (clock2.getElapsedTime().asSeconds() >= spawnTime3)
			{
				for (unsigned int i = 0; i < enemies3.size(); i++)
				{
					if (timer3.getElapsedTime().asSeconds() >= enemies3Time && enemies3[i].state != 1)
					{
						enemies3[i].state = 1;
						timer3.restart().asSeconds();
						enemies3Time = ((rand() % 9) + 8);
					}
					if (enemies3[i].eHP > 0)
						enemies3[i].Draw(window);
					enemies3[i].Update(deltaTime, 3);
				}
			}

			//Darkrise Spawn
			if (clock2.getElapsedTime().asSeconds() >= spawnTime4)
			{
				for (unsigned int i = 0; i < boss.size(); i++)
				{
					if (timer4.getElapsedTime().asSeconds() >= bossTime && boss[i].state != 2 && boss[i].state != 3)
					{
						boss[i].state = 0;
						timer4.restart().asSeconds();
					}
					if (boss[i].eHP > 0)
						boss[i].Draw(window);
					boss[i].Update(deltaTime, 4);
				}
			}

			if (projectile1.timer.getElapsedTime().asSeconds() < 0.3)
			{
				p = 0;
			}
			else if (projectile1.timer.getElapsedTime().asSeconds() >= 0.3 && projectile1.timer.getElapsedTime().asSeconds() < 0.6)
			{
				p = 1;
			}
			else projectile1.timer.restart();

			//Draw Projectile
			counter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				projectileArray[counter].Update(player.getPosition(), 1, p);
				window.draw(projectileArray[counter].sprite);
				counter++;
			}
			//Draw Projectile Boss
			if (clock2.getElapsedTime().asSeconds() >= 5)
			{
				counter4 = 0;
				for (iter = projectileArrayBoss.begin(); iter != projectileArrayBoss.end(); iter++)
				{
					projectileArrayBoss[counter4].Update(player.getPosition(), 4, p);
					window.draw(projectileArrayBoss[counter4].sprite);
					counter4++;
				}
			}
			printf("timer %f  ", projectile1.timer.getElapsedTime().asSeconds());
			printf("i %d\n", p);
			//Check Collision Player-Projectile-House-Ememy1
			for (unsigned int i = 0; i < enemies1.size(); i++)
			{
				if (enemies1[i].GetCollider().CheckCollision(platformHouse.GetCollider(), 1.0f, true))
				{
					player.isDead = true;
				}
				if (enemies1[i].GetCollider().CheckCollision(player.GetColliderP(), 1.0f, false) && Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::LShift))
				{
					if (dpsTimer.getElapsedTime().asSeconds() >= 0.5)
					{
						enemies1[i].eHP -= Dmg;
						if (sp <= 100) sp += 5;
						hitFX.play();
						dpsTimer.restart();
					}
				}
				if (enemies1[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, true))
				{
					enemies1[i].state = 0;
					if (dpsTimer.getElapsedTime().asSeconds() >= 0.5)
					{
						biteFX.play();
						dpsTimer.restart();
					}
					if (hp > 0) hp--;
				}
				else if (enemies1[i].state == 0)
				{
					if (!enemies1[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, true))
					{
						enemies1[i].state = 1;
					}
				}
				for (unsigned int j = 0; j < projectileArray.size(); j++)
				{
					if (enemies1[i].GetCollider().CheckCollision(projectileArray[j].GetCollider(), 1.0f, false) && enemies1[i].eHP > 0)
					{
						enemies1[i].eHP -= spDmg;
						spatkHitFX.play();
						projectileArray.erase(projectileArray.begin() + j);
					}
				}
			}
			//Check Collision Player-Projectile-House-Ememy2
			for (unsigned int i = 0; i < enemies2.size(); i++)
			{
				if (enemies2[i].GetCollider().CheckCollision(platformHouse.GetCollider(), 1.0f, true))
				{
					player.isDead = true;
				}
				if (enemies2[i].GetCollider().CheckCollision(player.GetColliderP(), 1.0f, false) && Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::LShift))
				{
					if (dpsTimer.getElapsedTime().asSeconds() >= 0.5)
					{
						enemies2[i].eHP -= Dmg;
						if (sp <= 100) sp += 5;
						hitFX.play();
						dpsTimer.restart();
					}
				}
				if (enemies2[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, true))
				{
					enemies2[i].state = 0;
					if (dpsTimer.getElapsedTime().asSeconds() >= 0.5)
					{
						biteFX.play();
						dpsTimer.restart();
					}
					if (hp > 0) hp--;
				}
				else if (enemies2[i].state == 0)
				{
					if (!enemies2[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, true))
					{
						enemies2[i].state = 1;
					}
				}
				for (unsigned int j = 0; j < projectileArray.size(); j++)
				{
					if (enemies2[i].GetCollider().CheckCollision(projectileArray[j].GetCollider(), 1.0f, false) && enemies2[i].eHP > 0)
					{
						enemies2[i].eHP -= spDmg;
						spatkHitFX.play();
						projectileArray.erase(projectileArray.begin() + j);
					}
				}
			}
			//Check Collision Player-Projectile-House-Ememy3
			for (unsigned int i = 0; i < enemies3.size(); i++)
			{
				if (enemies3[i].GetCollider().CheckCollision(platformHouse.GetCollider(), 1.0f, true))
				{
				player.isDead = true;
				}
				if (enemies3[i].GetCollider().CheckCollision(player.GetColliderP(), 1.0f, false) && Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::LShift))
				{
					if (dpsTimer.getElapsedTime().asSeconds() >= 0.5)
					{
						enemies3[i].eHP -= Dmg;
						if (sp <= 100) sp += 5;
						hitFX.play();
						dpsTimer.restart();
					}
				}
				if (enemies3[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, true))
				{
					enemies3[i].state = 0;
					if (dpsTimer.getElapsedTime().asSeconds() >= 0.5)
					{
						biteFX.play();
						dpsTimer.restart();
					}
					if (hp > 0) hp--;
				}
				else if (enemies3[i].state == 0)
				{
					if (!enemies3[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, true))
					{
						enemies3[i].state = 1;
					}
				}
				for (unsigned int j = 0; j < projectileArray.size(); j++)
				{
					if (enemies3[i].GetCollider().CheckCollision(projectileArray[j].GetCollider(), 1.0f, false) && enemies3[i].eHP > 0)
					{
						enemies3[i].eHP -= spDmg;
						spatkHitFX.play();
						projectileArray.erase(projectileArray.begin() + j);
					}
				}
			}

			//Check Collision Player-Projectile-House-Boss
			for (unsigned int i = 0; i < boss.size(); i++)
			{
				projectile2.body.setPosition(boss[i].getPosition().x - 80, boss[i].getPosition().y + 40);
				//Boss Atk
				if (clock2.getElapsedTime().asSeconds() > 5)
				{
					if (timer4.getElapsedTime().asSeconds() >= 2 && boss[0].eHP > 0)
					{
						if (timer4.getElapsedTime().asSeconds() <= 5)
						{
							if (counter5 != 0) counter5--;
							else
							{
								projectile2.directionPrj = player.directionPrj;
								projectileArrayBoss.push_back(projectile2);
								counter5 = 20;
							}
						}
						else if (timer4.getElapsedTime().asSeconds() >= 10)
							timer4.restart();
					}
				}
				for (unsigned int i = 0; i < projectileArrayBoss.size(); i++)
				{
					if (platformHouse.GetCollider().CheckCollision(projectileArrayBoss[i].GetCollider(), 1.0f, false))
					{
						projectileArrayBoss.erase(projectileArrayBoss.begin() + i);
					}
				}
	
				if (boss[i].GetCollider().CheckCollision(player.GetColliderP(), 1.0f, false) && Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::LShift))
				{
					if (dpsTimer.getElapsedTime().asSeconds() >= 0.5)
					{
						boss[i].eHP -= Dmg;
						if (sp <= 100) sp += 5;
						hitFX.play();
						dpsTimer.restart();
					}
				}
				if (boss[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, false))
				{
					if (hp > 0) hp--;
				}
				else if (boss[i].GetCollider().CheckCollision(platformHouse.GetCollider(), 1.0f, true))
				{
					player.isDead = true;
				}
				else
				{
					if (!boss[i].GetCollider().CheckCollision(player.GetColliders(), 1.0f, true))
					{
						if (boss[i].GetCollider().CheckCollision(platformb1.GetCollider(), 1.0, false) && bossCheck == 0)
						{
							bossCheck = 1;
							boss[i].state = 3;
							boss[i].bossHit = true;
						}
						if (boss[i].GetCollider().CheckCollision(platformb2.GetCollider(), 1.0, false) && bossCheck == 1)
						{
							bossCheck = 0;
							boss[i].state = 2;
							boss[i].bossHit = false;
						}
					}
				}
				for (unsigned int j = 0; j < projectileArray.size(); j++)
				{
					if (boss[i].GetCollider().CheckCollision(projectileArray[j].GetCollider(), 1.0f, false) && boss[i].eHP > 0)
					{
						boss[i].eHP -= spDmg;
						spatkHitFX.play();
						projectileArray.erase(projectileArray.begin() + j);
					}
				}
				for (unsigned int j = 0; j < projectileArrayBoss.size(); j++)
				{
					if (player.GetCollider().CheckCollision(projectileArrayBoss[j].GetCollider(), 1.0f, false) && boss[i].eHP > 0)
					{
						hp -= 80;
						spatkHitFX.play();
						projectileArrayBoss.erase(projectileArrayBoss.begin() + j);
					}
				}
			}

			//Item Check
			if (player.GetCollider().CheckCollision(items.GetCollider(), 0.0f, true) && isPick)
			{
				itemFX.play();
				if (hp >= 0 && hp <= 880) hp += 120;
				else if (hp > 880) hp = 1000;
				itemTime.restart().asSeconds();
				Posx = 9000.0f;
				Posy = 0.0f;
				isPick = false;
			}

			//Erase Enemy
			for (unsigned int i = 0; i < enemies1.size(); i++)
			{
				if (enemies1[i].eHP <= 0)
				{
					enemies1.erase(enemies1.begin() + i);
					Score += 150;
				}
			}
			for (unsigned int i = 0; i < enemies2.size(); i++)
			{
				if (enemies2[i].eHP <= 0)
				{
					enemies2.erase(enemies2.begin() + i);
					Score += 300;
				}
			}
			for (unsigned int i = 0; i < enemies3.size(); i++)
			{
				if (enemies3[i].eHP <= 0)
				{
					enemies3.erase(enemies3.begin() + i);
					Score += 700;
				}
			}
			for (unsigned int i = 0; i < boss.size(); i++)
			{
				if (boss[i].eHP <= 0)
				{
					boss.erase(boss.begin() + i);
					Score += 2000;
				}
			}

			//Win Check
			if ((enemies1.empty() && enemies2.empty() && enemies3.empty() && lvl == 1 && !winCheck) || Keyboard::isKeyPressed(Keyboard::Num1))
			{
				win1 = true;
				lvl = 2;
				isWin = true;
				winCheck = true;
			}
			else if ((enemies1.empty() && enemies2.empty() && enemies3.empty() && lvl == 2 && win1 && !winCheck) || Keyboard::isKeyPressed(Keyboard::Num2))
			{
				win2 = true;
				lvl = 3;
				isWin = true;
				winCheck = true;
			}
			else if ((enemies1.empty() && enemies2.empty() && enemies3.empty() && lvl == 3 && win2 && !winCheck) || Keyboard::isKeyPressed(Keyboard::Num3))
			{
				win3 = true;
				lvl = 4;
				isWin = true;
				winCheck = true;
			}
			else if ((enemies1.empty() && enemies2.empty() && enemies3.empty() && boss.empty() && lvl == 4 && !winCheck) || Keyboard::isKeyPressed(Keyboard::Num4))
			{
				win4 = true;
				isWin = true;
				winCheck = true;
				Win = true;
			}

			//Pow ReGen
			if (sp <= 100)
			{
				sp += 0.1f;
			}
			else if (sp > 100) sp = 100;

			HP.setSize(Vector2f(hp / 3.18f, 21.0f));
			SP.setSize(Vector2f(sp / 0.318f, 21.0f));
			cursor.loadFromSystem(Cursor::Arrow);
			window.setMouseCursor(cursor);
			window.draw(hpbar);
			window.draw(HP);
			window.draw(SP);
			items.Draw(window);
			platformUp.Draw(window);
			platformDown.Draw(window);
			platformLeft.Draw(window);
			platformRight.Draw(window);
			platformb2.Draw(window);
			platformb1.Draw(window);
			window.display();
		}
		//How to Loop
		if (mode == 5)
		{
			howtoSound.play();
		}
		else if (mode == 1)
			music.play();
		while (mode == 5)
		{
			mouse = Mouse::getPosition(window);
			Event scoreEvent;
			view.setCenter(700.0f, 300.0f);
			back0.loadFromFile("photo/menu/back0.png");
			back1.loadFromFile("photo/menu/back1.png");

			//Game Clock Reset
			clock2.restart().asSeconds();
			deltaTime = clock.restart().asSeconds();

			while (window.pollEvent(scoreEvent))
			{
				switch (scoreEvent.type)
				{
				case Event::Closed:
					howtoSound.stop();
					window.close();
					exit(0);
					break;
				case Event::MouseButtonPressed:
					if (scoreEvent.mouseButton.button == Mouse::Left)
					{
						if ((mouse.x > 870 && mouse.x < 1156 && mouse.y > 684 && mouse.y < 723))
						{
							buttonPressedSound.play();
							howtoSound.stop();
							mode = 0;
						}
					}
				}
			}
			window.clear();
			window.draw(howtoSprite);
			if (mouse.x > 870 && mouse.x < 1156 && mouse.y > 684 && mouse.y < 723)
			{
				cursor.loadFromSystem(Cursor::Hand);
				window.draw(sback1);
			}
			else
			{
				cursor.loadFromSystem(Cursor::Arrow);
				window.draw(sback0);
			}
			window.setMouseCursor(cursor);
			window.setView(view);
			window.display();
		}

		//End Game Loop
		if (mode == 4)
		{
			music.stop();
			endSongSound.play();
		}	
		else if (mode == 1)
			music.play();
		while (mode == 4)
		{
			view.setCenter(700.0f, 300.0f);
			if (Win) endTexture.loadFromFile("photo/menu/win.png");
			else endTexture.loadFromFile("photo/menu/lose.png");
			endTexture.setSmooth(true);
			Sprite endSprite;
			endSprite.setTexture(endTexture);
			score.setCharacterSize(45);
			score.setFont(font4);
			score.setOutlineThickness(0);
			score.setFillColor(sf::Color::Black);
			mouse = Mouse::getPosition(window);
			Event scoreEvent;
			back0.loadFromFile("photo/menu/back2.png");
			back1.loadFromFile("photo/menu/back3.png");

			//Game Clock Reset
			clock2.restart().asSeconds();
			itemTime.restart().asSeconds();
			deltaTime = clock.restart().asSeconds();

			while (window.pollEvent(scoreEvent))
			{
				if (scoreEvent.type == Event::TextEntered && !nameEntered)
				{
					if (scoreEvent.text.unicode == '\r')
					{
						if (yourname.size() > 0)
						{
							ofstream myFile;
							myFile.open("score.txt", ios::out | ios::app);
							myFile << "\n" << yourname << " " << Score;
							myFile.close();
						}
						nameEntered = true;
						tplayer.setFillColor(Color::Black);
						buttonPressedSound.play();
						endSongSound.stop();
						winFX.stop();
						music.stop();
						tplayer.setString("");
						mode = 0;
					}
					else if (scoreEvent.text.unicode == '\b')
					{
						if (yourname.size() > 0)
						{
							yourname.erase(yourname.size() - 1, 1);
							tplayer.setFont(font4);
							tplayer.setFillColor(Color::Blue);
							tplayer.setString(yourname);
						}
					}
					else 
					{
						if ((scoreEvent.text.unicode < 128) && (yourname.size() < 8) && (scoreEvent.text.unicode != 32))
						{
							string name;
							yourname += static_cast<char>(scoreEvent.text.unicode);
							name += static_cast<char>(scoreEvent.text.unicode);
							tplayer.setFont(font4);
							tplayer.setFillColor(Color::Blue);
							tplayer.setString(yourname);
						}
					}
					tplayer.setCharacterSize(45);
					tplayer.setPosition(580.0f, 385.0f);  //ตำแหน่งของข้อความ
				}
				else if (scoreEvent.type == Event::KeyPressed)
				{
					if (scoreEvent.key.code == Keyboard::Return) 
					{
						tplayer.setString(yourname);
					}
				}
				if (scoreEvent.type == Event::Closed)
				{
					window.close();
					exit(0);
				}
				if (scoreEvent.type == Event::MouseButtonPressed)
					if (scoreEvent.mouseButton.button == Mouse::Left)
					{
						if ((mouse.x > 870 && mouse.x < 1156 && mouse.y > 684 && mouse.y < 724))
						{
							buttonPressedSound.play();
							endSongSound.stop();
							music.stop();
							mode = 3;
							exit(0);
						}
					}
			}

			window.clear();
			window.draw(endSprite);
			if (mouse.x > 870 && mouse.x < 1156 && mouse.y > 684 && mouse.y < 723)
			{
				cursor.loadFromSystem(Cursor::Hand);
				window.draw(sback1);
			}
			else
			{
				cursor.loadFromSystem(Cursor::Arrow);
				window.draw(sback0);
			}
			score.setPosition(620, 270);
			window.setMouseCursor(cursor);
			window.setView(view);
			window.draw(score);
			window.draw(tplayer);
			window.display();
		}
		scoreboard.push_back({ Score,yourname });
		sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, string>>());
	}
	return 0;
}