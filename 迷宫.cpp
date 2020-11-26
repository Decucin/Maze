#include <iostream>
#include "MazeStack.h"
#include "Maze.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(void) {
	MazeType maze;

	cout << "请输入迷宫的行数和列数:";
	int** map;
	int m, n;
	PosType start, end;
	
	cin >> m >> n;
	
	start = { 0,0 };
	end = { m - 1, n - 1 };

	map = new int* [m];
	for (int i = 0; i < m; i++)
		map[i] = new int[n];
	do{
		srand(time(0));

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				map[i][j] = rand() % 2;
			}
		}

		map[0][0] = map[m - 1][n - 1] = 0;
		
		InitMaze(&maze, map, m, n);
		
	} while (!MazePath(maze, start, end));

	PrintMaze(maze);

	return 0;
}