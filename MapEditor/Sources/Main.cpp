#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Field.h"
#include "Map.h"

using namespace sf;
using namespace std;

int main()
{
	RenderWindow* window = new RenderWindow(VideoMode(1000.f, 800.f), "Testy pól");
	window->setFramerateLimit(60);
	View map_view(FloatRect(0.f, 0.f, 800.f, 800.f));
	View palet_view(FloatRect(0.f, 0.f, 200.f, 800.f));
	map_view.setViewport(FloatRect(0, 0, 0.8f, 1));
	palet_view.setViewport(FloatRect(0.8f, 0, 0.2, 1));
	
	float map_scrl_spd = 5;
	int brushType = 0;
	
	Map* palet = new Map();
	Map* map = new Map();
	
	palet->setField(0, 0, 1);
	palet->setField(0, 1, 1);
	palet->setField(1, 1, 4);
	palet->setField(2, 1, 3);
	palet->setField(2, 0, 2);


	
	while (window->isOpen()) {
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
			}
		}

		Vector2i MPos = Mouse::getPosition(*window);
		window->setView(map_view);
		Vector2f MPosMap = window->mapPixelToCoords(MPos);
		
		window->setView(palet_view);
		Vector2f MPosPalet = window->mapPixelToCoords(MPos);
		
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			map->saveMapFile();
		}
		if (Keyboard::isKeyPressed(Keyboard::L)) {
			map->loadMapFile();
		}
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			int x, y;
			cout << "x: ";
			cin >> x;
			cout << "y: ";
			cin >> y;
			map->setMapSize(x,y);
		}
		
		//przesuwanie mapy
		
		
		if (MPos.x >= 760 && MPos.x <= 800 && map_view.getCenter().x + map_view.getSize().x/2 < 2000) {
			map_view.move(map_scrl_spd, 0);

		}else if (MPos.x >= 0 && MPos.x <= 40 && map_view.getCenter().x - map_view.getSize().x / 2 > -50) {
			map_view.move(-map_scrl_spd, 0);
		}

		if (MPos.y >= 760 && MPos.y <= 800 && map_view.getCenter().y + map_view.getSize().y / 2 < 1600) {
			map_view.move(0, map_scrl_spd);
		}
		else if (MPos.y >= 0 && MPos.y <= 40 && map_view.getCenter().y - map_view.getSize().y / 2 > -50) {
			map_view.move(0, -map_scrl_spd);
		}
		//koniec przesuwania

		if (Mouse::isButtonPressed(Mouse::Left) && MPos.x < 800) {
			map->setField(MPosMap.x / 50, MPosMap.y / 50, brushType);
		}

		
		if (Mouse::isButtonPressed(Mouse::Left) && MPos.x > 800) {
			cout << MPosPalet.x << " \ " << MPosPalet.y << endl;

			brushType = palet->getField(MPosPalet);

			cout << brushType << endl;
		}

		

		window->setView(map_view);
		window->clear(Color(100,150,255));
		window->draw(*map);
		window->setView(palet_view);
		window->draw(*palet);
		window->display();
	}

	return 0;
}