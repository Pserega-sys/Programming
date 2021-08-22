#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
#include <cassert>

using namespace sf;

const int M = 22; // ������ �������� ����
const int N = 12; // ������ �������� ����

void menu(RenderWindow& window)
{
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("texture\\newG.png");
	menuTexture2.loadFromFile("texture\\Aprog.png");
	menuTexture3.loadFromFile("texture\\exit.png");
	aboutTexture.loadFromFile("texture\\inform.png");
	menuBackground.loadFromFile("texture\\MBack.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(70, 30);
	menu2.setPosition(70, 90);
	menu3.setPosition(70, 150);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1.setColor(Color::Yellow);
		menu2.setColor(Color::Green);
		menu3.setColor(Color::Cyan);
		menuNum = 0;

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;// ���� ������ ������ ������, �� ������� �� ���� � �������� ����
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); } // � ���������
			if (menuNum == 3) { window.close(); isMenu = false; } // �����

		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();

	}
}

int field[M][N] = { 0 }; // ������� ����
// ������ �����-���������
int figures[7][4] =
{
	3,5,7,6, // J
	1,3,5,7, // I
	2,3,4,5, // O
	2,3,5,7, // L
	2,4,5,7, // Z
	3,5,4,7, // T
	3,5,4,6, // S
};

struct Point
{
	int x, y;
} a[4], b[4];

// �������� �� ����� �� ������� �������� ����
bool check()
{

	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if (field[a[i].y][a[i].x]) return 0;

	return 1;

};

bool Gamerun()
{

	srand(time(0));

	RenderWindow window(VideoMode(420, 580), "The TETRIS!");
	menu(window); // ����� ����

	// �������� � �������� �������
	Texture texture, texture_ramka, texture_background;
	texture.loadFromFile("texture\\tetramino.png");
	texture_ramka.loadFromFile("texture\\ramka12.png");
	texture_background.loadFromFile("texture\\background.png");

	// �������� ��������
	Sprite sprite(texture), sprite_ramka(texture_ramka), sprite_background(texture_background);

	// �������� �� ������� ��������� ��������� �������� 18�18 ��������
	sprite.setTextureRect(IntRect(0, 0, 18, 18));

	// ���������� ��� ��������������� ����������� � ��������
	int dx = 0; bool rotate = 0; int colorNum = 1; bool beginGame = true; int n = rand() % 7;

	// ���������� ��� ������� � ��������
	float timer = 0, delay = 0.3;

	// ���� (������)
	Clock clock;

	while (window.isOpen()) // ������� ���� ����������
	{
		// �������� �����, ��������� � ������ �������, � ������������ ��� � �������
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) // ���� ������������ ����� �� ������� �� ��������� ����������
			{
				return false;
			}

			if (event.type == Event::KeyPressed) // ���� ���� ������ ������ �� ���������� ��:

				if (event.key.code == Keyboard::Up) rotate = true; // ��������
				else if (event.key.code == Keyboard::Left) dx = -1; // �������� �����
				else if (event.key.code == Keyboard::Right) dx = 1; // �������� ������
		}
		// ����� ������������� ������ ������ ���� ��� ��������� ������� ������� ���������
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; } // ���� ������, �� ������� �� ����

		// �������������� ����������� ����� 
		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }

		// ����� �� ������� ���� ����� �����������? ����� ������������ ������ ���������� 
		if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

		// �������� ����� 
		if (rotate)
		{
			Point p = a[1]; // ������ ����� ��������
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y; //y-y0
				int y = a[i].x - p.x; //x-x0
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			// ����� �� ������� ���� ����� ��������? ����� ���������� ������ ���������� 
			if (!check()) { for (int i = 0; i < 4; i++) a[i] = b[i]; }

		}

		// �������� ��������� ���� (��� �������)
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
			if (!check())
			{
				for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
				colorNum = 1 + rand() % 7;
				n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}

			}
			timer = 0;

		}

		// �������� ����� ���� �� �� ������������� ��������� 
		int k = M - 1;
		for (int i = M - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < N; j++)
			{
				if (field[i][j]) count++;
				field[k][j] = field[i][j];
			}
			if (count < N) k--;
		}
		// ������ ��������� ��������� �� ����
		if (beginGame)
		{
			beginGame = false;
			n = rand() % 7;
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}
		dx = 0; rotate = 0; delay = 0.3;

		// ���������� //
		window.draw(sprite_background);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) continue;
				sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				sprite.setPosition(j * 18, i * 18);
				sprite.move(101, 71); // ��������
				window.draw(sprite);
			}
		for (int i = 0; i < 4; i++)
		{
			// ������������� ���������
			sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));

			// ������������� ������� ������� ������� ���������
			sprite.setPosition(a[i].x * 18, a[i].y * 18);

			sprite.move(101, 71); // ��������

			// ��������� �������
			window.draw(sprite);
		}
		// ��������� ������
		window.draw(sprite_ramka);
		// ��������� ����
		window.display();

		void GameOver();
		{
			for (int i = 0; i < N; i++)
			{
				if (field[1][i])
				{
					Texture Gameover;
					Gameover.loadFromFile("texture\\over.png");
					Sprite over1(Gameover);
						window.draw(over1);
						window.display();
						while (exit) {
						if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; } }
					std::cout << "end";
				}
			}
		}
	}
}

int main()
{
	Gamerun();
	return 0;
}
