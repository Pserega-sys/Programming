#include <SFML/Graphics.hpp>
 
using namespace sf;
 
int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(1000, 600), "Towerd");
	
	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}

	// Задаем цвет фона
	window.clear(Color::Green);

	// Загрузка текстур
	Texture tx_road;
	Texture mesto;
	Texture tower1;
	Texture enemy;

	mesto.loadFromFile("C:\\dev\\towerd\\texture\\texture_bricks.jpg");
	tx_road.loadFromFile("C:\\dev\\towerd\\texture\\texture_road.jpg");
	tx_road.setRepeated(true);
	tower1.loadFromFile("C:\\dev\\towerd\\texture\\tower1.png");
	enemy.loadFromFile("C:\\dev\\towerd\\texture\\enemy.jpg");

	Sprite enemy1(enemy);


	// Горизонтальное перемещение
	int dx = 997;

	//for (int i = 0; i < 4; i++) a[i].x += dx;

	//int n = 3;



	// Создание спрайтов дорог

	Sprite road(tx_road, IntRect(0, 0, 400, 60));
	Sprite road2(tx_road, IntRect(0, 0, 200, 60));
	Sprite road3(tx_road, IntRect(0, 0, 590, 60));

	// Спрайт для мест по башни
	Sprite mesto1(mesto);
	Sprite mesto2(mesto);
	Sprite mesto3(mesto);
	Sprite mesto4(mesto);
	Sprite mesto5(mesto);
	Sprite mesto6(mesto);

	// Спрайт-текстура башни
	Sprite tower(tower1);
	Sprite tower2(tower1);
	Sprite tower3(tower1);
	Sprite tower4(tower1);
	Sprite tower5(tower1);
	Sprite tower6(tower1);

	// Ворота
	RectangleShape gate(Vector2f(5.f, 60.f));
	RectangleShape gate2(Vector2f(6.f, 60.f));

	// Уменьшение текстур
	tower.setScale(0.6f, 0.6f);
	mesto1.setScale(0.4f, 0.4f);
	tower2.setScale(0.6f, 0.6f);
	mesto2.setScale(0.4f, 0.4f);
	tower3.setScale(0.6f, 0.6f);
	mesto3.setScale(0.4f, 0.4f);
	tower4.setScale(0.6f, 0.6f);
	mesto4.setScale(0.4f, 0.4f);
	tower5.setScale(0.6f, 0.6f);
	mesto5.setScale(0.4f, 0.4f);
	tower6.setScale(0.6f, 0.6f);
	mesto6.setScale(0.4f, 0.4f);
	enemy1.setScale(0.2f, 0.2f);

	// Поворачиваем дорогу 2 на 45 градусов
	road2.rotate(90.f);

	// Устанавливаем цвет
	gate.setFillColor(Color(255, 0, 0));
	gate2.setFillColor(Color(255, 0, 0));

	// Перемещаем обекты
	gate.move(0, 130);
	gate2.move(994, 270);
	road.move(5, 130);
	road2.move(405, 130);
	road3.move(405, 270);

	//Перемещение башен и мест
	mesto1.move(191, 73);
	tower.move(130, -40);
	mesto2.move(191, 243);
	tower2.move(130, 130);
	mesto3.move(500, 213);
	tower3.move(439, 100);
	mesto4.move(779, 213);
	tower4.move(718, 100);
	mesto5.move(500, 383);
	tower5.move(439, 270);
	mesto6.move(779, 383);
	tower6.move(718, 270);

	// Отрисовка дорог и мест для башен
	window.draw(gate);
	window.draw(gate2);
	window.draw(road);
	window.draw(road2);
	window.draw(road3);

	// Отрисовка мест под башни
	window.draw(mesto1);
	window.draw(mesto2);
	window.draw(mesto3);
	window.draw(mesto4);
	window.draw(mesto5);
	window.draw(mesto6);

	// Отрисовка башен
	//
	window.draw(tower);
	window.draw(tower2);
	window.draw(tower3);
	window.draw(tower4);
	window.draw(tower5);
	window.draw(tower6);

	window.draw(enemy1);

	// Отрисовка окна	
	window.display();
	}
 
	return 0;
}