#include <SFML/Graphics.hpp>
#include "Drawer.h"
#include "TicTacToe.h"
using namespace sf;

#include <iostream>
#include <fstream>
using namespace std;
int gridSize = 3, winCondition = 3, n = 2;
string font = "font.ttf";
void loadSettings(RenderWindow& window) {
	int height = 600, width = 600;
	ifstream settings("settings.txt");
	if (!settings.is_open()) {
		window.create(VideoMode(height, width), "TicTacToe");
		return;
	}
	else {
		string str;
		while (settings >> str) {
			if (str == "windowheight") {
				settings >> str;
				try { height = stoi(str); }
				catch (exception& err) { height = 600; }
			}
			else if (str == "windowwidth") {
				settings >> str;
				try { width = stoi(str); }
				catch (exception& err) { width = 600; }
			}
			else if (str == "font") {
				settings >> str;
				font = str;
			}
			else if (str == "gridsize") {
				settings >> str;
				try { gridSize = stoi(str); }
				catch (exception& err) { gridSize = 3; }
			}
			else if (str == "wincondition") {
				settings >> str;
				try { winCondition = stoi(str); }
				catch (exception& err) { winCondition = 3; }
			}
			else if (str == "nofplayers") {
				settings >> str;
				try { n = stoi(str); }
				catch (exception& err) { n = 2; }
			}
		}
		window.create(VideoMode(height, width), "TicTacToe");
	}
	
}
int main() {
	RenderWindow window;
	loadSettings(window);
	TicTacToe* game = new TicTacToe(gridSize, winCondition);
	TicTacToeDrawer drawer(window, game, font, n);
	drawer.gridColor = Color(250, 218, 221);
	drawer.thickness = 1;
	while (window.isOpen()) {
		Event event;
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
				drawer.move(mouse.x / drawer.squareSizeX, mouse.y / drawer.squareSizeY);
			}
			if (event.type == Event::KeyPressed) {
				switch (event.key.code) {
				case 17:
					game = new TicTacToe(gridSize, winCondition);
					drawer.reset();
					break;
				}
			}
		}
		window.clear(Color(245, 245, 220));
		
		drawer.draw();
		window.display();
	}

	return 0;
}