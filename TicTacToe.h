#pragma once
#include <algorithm>
#include <cassert>
#include <vector>

class TicTacToe {
private:
	short int** grid;
public:
	unsigned int gridSize, winCondition, moves = 0, lastMoveX = -1, lastMoveY = -1;
	TicTacToe(int gridSize = 3, int winCondition = 3) : gridSize(gridSize), winCondition(winCondition) {
		grid = new short int*[gridSize];
		for (int x = 0; x < gridSize; ++x) {
			grid[x] = new short int[gridSize];
			for (int y = 0; y < gridSize; ++y) {
				grid[x][y] = 0;
			}
		}
	}
	int checkForWinnerNew() {
		int team = 0, times = 0;
		// horizontally
		for (int x = 0; x < gridSize; ++x) {
			if (team != grid[x][lastMoveY]) {
				times = 0;
				team = grid[x][lastMoveY];
			}
			if (team != 0 && times >= winCondition - 1) {
				return team;
			}
			++times;
		}
		// vertically
		team = 0, times = 0;
		for (int y = 0; y < gridSize; ++y) {
			if (team != grid[lastMoveX][y]) {
				times = 0;
				team = grid[lastMoveX][y];
			}
			if (team != 0 && times >= winCondition - 1) {
				return team;
			}
			++times;
		}
		// diagonally 1
		int fromX = 0, fromY = 0;
		if (lastMoveX > lastMoveY) {
			fromX = lastMoveX - lastMoveY;
			fromY = 0;
		}
		if (lastMoveX < lastMoveY) {
			fromX = 0;
			fromY = lastMoveY - lastMoveX;
		}
		team = 0, times = 0;
		for (int xy = 0; xy < gridSize && fromX + xy < gridSize && fromY + xy < gridSize; ++xy) {
			if (team != grid[fromX + xy][fromY + xy]) {
				times = 0;
				team = grid[fromX + xy][fromY + xy];
			}
			if (team != 0 && times >= winCondition - 1) {
				return team;
			}
			++times;
		}
		// diagonally 2
		int N = std::min(gridSize - lastMoveX - 1, lastMoveY);
		fromX = lastMoveX + N;
		fromY = lastMoveY - N;
		team = 0, times = 0;
		for (int xy = 0; xy < gridSize && fromX - xy >= 0 && fromY + xy < gridSize; ++xy) {
			if (team != grid[fromX - xy][fromY + xy]) {
				times = 0;
				team = grid[fromX - xy][fromY + xy];
			}
			if (team != 0 && times >= winCondition - 1) {
				return team;
			}
			++times;
		}
		return 0;
	}
	bool checkForDraw() {
		return (moves == gridSize * gridSize);
	}
	short int& move(unsigned int x, unsigned int y) {
		assert((x >= 0 && x < gridSize) && (y >= 0 && y < gridSize));
		lastMoveX = x;
		lastMoveY = y;
		++moves;
		return grid[x][y];
	}
	short int operator()(unsigned int x, unsigned int y) {
		assert((x >= 0 && x < gridSize) && (y >= 0 && y < gridSize));
		return grid[x][y];
	}
	~TicTacToe() {
		delete[] grid;
	}
};