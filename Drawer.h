#pragma once
#include <SFML/Graphics.hpp>
#include "Drawer_Textures.h"
#include "TicTacToe.h"
class TicTacToeDrawer {
private:
	sf::RenderWindow& window;
	sf::Font font;
	TicTacToe*& game;
	int playerToMove = 0, winner = 0;
	Textures textures;
	std::vector<std::pair<int, double>> totalScore;
	std::string fontStr;
public:
	double thickness = 1, squareSizeX, squareSizeY;
	sf::Color gridColor = { 255, 255, 255 };
	TicTacToeDrawer(sf::RenderWindow& window, TicTacToe*& game, std::string fontStr, int nOfPlayers) : window(window), game(game), fontStr(fontStr) {
		textures.loadTextures(nOfPlayers);
		squareSizeX = window.getSize().x / game->gridSize;
		squareSizeY = window.getSize().y / game->gridSize;
		font.loadFromFile(fontStr);
		totalScore.resize(textures.n);
		for (int i = 0; i < totalScore.size(); ++i) {
			++totalScore[i].first;
		}
	}
	void draw() {
		sf::RectangleShape temp;
		temp.setFillColor(gridColor);
		temp.setSize(sf::Vector2f(squareSizeX - thickness, squareSizeY - thickness));
		for (int x = 0; x < game->gridSize; ++x) {
			for (int y = 0; y < game->gridSize; ++y) {
				sf::Sprite player;
				temp.setPosition(x * squareSizeX + thickness / 2, y * squareSizeY + thickness / 2);
				window.draw(temp);
				if ((*game)(x, y)) {
					player.setPosition(x * squareSizeX + temp.getSize().x / 4, y * squareSizeY + temp.getSize().y / 4);
					player.setTexture(textures.getTexture((*game)(x, y) - 1));
					player.setScale(1.0 / textures.getTexture((*game)(x, y) - 1).getSize().x / (1.0 / squareSizeX) / 2.0, 1.0 / textures.getTexture((*game)(x, y) - 1).getSize().y / (1.0 / squareSizeY) / 2.0);
					window.draw(player);
				}
			}
		}
	}
	void move(int x, int y) {
		if (!((x >= 0 && x < game->gridSize) && (y >= 0 && y < game->gridSize)))
			return;
		if (!winner) {
			if ((*game)(x, y) == 0) {
				(*game)(x, y) = playerToMove + 1;
				++playerToMove;
				if (playerToMove >= textures.n) {
					playerToMove = 0;
				}
				winner = game->checkForWinner();
				if (winner) {
					++totalScore[winner - 1].second;
					std::cout << "Player " << winner << " win!\n\n";
					std::cout << "Current score: ";
					for (int i = 0; i < totalScore.size(); ++i) {
						std::cout << "\nPlayer " << i + 1 << ". Score: " << totalScore[i].second;
					}
					std::cout << "\n\nPress R to restart";
				}
				if (game->checkForDraw()) {
					std::cout << "Draw!\n";
					std::cout << "Current score: ";
					for (int i = 0; i < totalScore.size(); ++i) {
						totalScore[i].second += 1.0 / totalScore.size();
						std::cout << "\nPlayer " << i + 1 << ". Score: " << totalScore[i].second;
					}
					std::cout << "\n\nPress R to restart";
				}
			}
		}
	}
	void reset() {
		playerToMove = 0;
		winner = 0;
		std::cout << "\033c"; // reset terminal
	}
};