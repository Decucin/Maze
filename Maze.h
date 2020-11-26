#pragma once
#include <iostream>
#include "MazeStack.h"

using namespace std;

void InitMaze(MazeType* maze, int **a, int row, int col);
bool MazePath(MazeType& maze, PosType start, PosType end);
void PrintMaze(MazeType maze);
bool Pass(MazeType maze, PosType curpos);
void FootPrint(MazeType *maze, PosType curpos);
bool Same(PosType curpos, PosType end);
PosType NextPos(PosType curpos, directiveType di);
void MarkPrint(MazeType *maze, PosType seat);

void InitMaze(MazeType* maze, int** a, int row, int col) {
	maze->r = row;
	maze->c = col;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			maze->arr[i][j] = a[i][j];
		}
	}

	return;
}

bool MazePath(MazeType& maze, PosType start, PosType end) {
	
	MazeStack* S = (MazeStack *)malloc(sizeof(MazeStack));
	
	InitMazeStack(S);

	PosType curpos = start;
	int curstep = 1;
	bool found = false;
	MSElemType e;
	
	do {
		if (Pass(maze, curpos)) {
			FootPrint(&maze, curpos);
			e = {curstep, curpos, 1};
			Push(S, e);
			if (Same(curpos, end))
				found = true;
			curpos = NextPos(curpos, 1);
			curstep++;
		}

		else {
			if (!MazeStackEmpty(S)) {
				Pop(S, &e);
				while (e.di == 4 && !MazeStackEmpty(S)) {
					MarkPrint(&maze, e.seat);
					Pop(S, &e);
					curstep--;
				}
				if (e.di < 4) {
					e.di++;
					Push(S, e);
					curpos = NextPos(e.seat, e.di);
				}
			}
		}

	} while ((!MazeStackEmpty(S)) && (!found));

	return found;
}

void PrintMaze(MazeType maze){
	for (int i = 0; i < maze.r; i++) {
		for (int j = 0; j < maze.c; j++) {
			cout << maze.arr[i][j]<<',';
		}
		cout << endl;
	}
}

bool Pass(MazeType maze, PosType curpos) {
	if (maze.arr[curpos.r][curpos.c] == 0)
		return true;
	else
		return false;
}

void FootPrint(MazeType *maze, PosType curpos) {
	maze->arr[curpos.r][curpos.c] = 2;
	return;
}

bool Same(PosType curpos, PosType end)
{
	if (curpos.r == end.r && curpos.c == end.c)
		return true;
	else
		return false;
}

PosType NextPos(PosType curpos, directiveType di)
{
	PosType pos = curpos;
	switch (di) {
		case 1:
			pos.c++;
			break;
		case 2:
			pos.r++;
			break;
		case 3:
			pos.c--;
			break;
		case 4:
			pos.r--;
			break;
	}
	return pos;
}

void MarkPrint(MazeType *maze, PosType seat) {
	maze->arr[seat.r][seat.c] = -1;
	return;
}