#pragma once
#include <cassert>
#include <vector>

class TicTacToe {
private:
	short int** grid;
public:
	unsigned int gridSize, winCondition;
	TicTacToe(int gridSize = 3, int winCondition = 3) : gridSize(gridSize), winCondition(winCondition) {
		grid = new short int*[gridSize];
		for (int x = 0; x < gridSize; ++x) {
			grid[x] = new short int[gridSize];
			for (int y = 0; y < gridSize; ++y) {
				grid[x][y] = 0;
			}
		}
	}
	int checkForWinner() {
		// vertical and gorizontal
		int teamX = 0, timesX = 0, teamY = 0, timesY = 0;
		for (int x = 0; x < gridSize; ++x) {
			for (int y = 0; y < gridSize; ++y) {
				if (teamX != grid[y][x]) {
					timesX = 0;
					teamX = grid[y][x];
				}
				if (teamY != grid[x][y]) {
					timesY = 0;
					teamY = grid[x][y];
				}
				if (teamX != 0 && timesX >= winCondition - 1) {
					return teamX;
				}
				if (teamY != 0 && timesY >= winCondition - 1) {
					return teamY;
				}
				++timesX;
				++timesY;
			}
			timesX = 0;
			timesY = 0;
		}
		// diagonal 1
		std::vector<std::vector<int> > ans(gridSize * 2 - 1);

		for (int x = 0; x < gridSize; ++x) {
			for (int y = 0; y < gridSize; ++y) {
				ans[x + y].push_back(grid[y][x]);
			}
		}
		teamX = 0, timesX = 0, teamY = 0, timesY = 0;
		for (int x = 0; x < ans.size(); ++x) {
			for (int y = 0; y < ans[x].size(); ++y) {
				if (teamX != ans[x][y]) {
					timesX = 0;
					teamX = ans[x][y];
				}
				if (teamX != 0 && timesX >= winCondition - 1) {
					return teamX;
				}
				++timesX;
			}
			timesX = 0;
		}

		for (int i = 0; i < ans.size(); ++i) {
			ans[i].clear();
		}

		// diagonal 2
		for (int x = 0; x < gridSize; ++x) {
			for (int y = 0; y < gridSize; ++y) {
				ans[x + y].push_back(grid[y][gridSize - x - 1]);
			}
		}
		teamX = 0, timesX = 0, teamY = 0, timesY = 0;
		for (int x = 0; x < ans.size(); ++x) {
			for (int y = 0; y < ans[x].size(); ++y) {
				if (teamX != ans[x][y]) {
					timesX = 0;
					teamX = ans[x][y];
				}
				if (teamX != 0 && timesX >= winCondition - 1) {
					return teamX;
				}
				++timesX;
			}
			timesX = 0;
		}
		return 0;
	}
	bool checkForDraw() {
		for (int x = 0; x < gridSize; ++x) {
			for (int y = 0; y < gridSize; ++y) {
				if (!grid[x][y]) {
					return 0;
				}
			}
		}
		return 1;
	}
	short int& operator()(unsigned int x, unsigned int y) {
		assert((x >= 0 && x < gridSize) && (y >= 0 && y < gridSize));
		return grid[x][y];
	}
	~TicTacToe() {
		delete[] grid;
	}
};