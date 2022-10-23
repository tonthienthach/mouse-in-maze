// De_Tai_Cuoi_Ki.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <string>

// C++ program to solve Rat in a Maze problem using
// backtracking

using namespace std;
// Maze size
#define N 8
// cho kich thuoc la 8
int startx, starty;
int goalx, goaly;
int sol[N][N];

bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]);

// A utility function to print solution matrix sol[N][N]
//void printSolution(int sol[N][N])
//{
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++)
//			cout << " " << sol[i][j] << " ";
//		cout << endl;
//	}
//}

void printSolution(string solu[N][N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << " " << solu[i][j] << " ";
		cout << endl;
	}
}

void changeArrayToChar(string solu[N][N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			if ((sol[i][j] == 1 && sol[i][j + 1] == 1) || (sol[i][j] == 1 && sol[i][j - 1] == 1))
				solu[i][j] = 45;
			else if((sol[i][j] == 1 && sol[i + 1][j] == 1) || (sol[i][j] == 1 && sol[i - 1][j] == 1))
				solu[i][j] = 124;
	}
}

void scanSolution(int maze[N][N], string solu[N][N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			solu[i][j] = to_string(maze[i][j]);
		cout << endl;
	}
}

// A utility function to check if x, y is valid index for
// N*N maze
bool isSafe(int maze[N][N], int x, int y)
{
	// if (x, y outside maze) return false
	if (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1)
		return true;
	return false;
}

// This function solves the Maze problem using Backtracking.
// It mainly uses solveMazeUtil() to solve the problem. It
// returns false if no path is possible, otherwise return
// true and prints the path in the form of 1s. Please note
// that there may be more than one solutions, this function
// prints one of the feasible solutions.
bool solveMaze(int maze[N][N])
{
	string solu[N][N];
	scanSolution(maze, solu);
	/*int sol[N][N] = { { 0, 0, 0, 0, 0 },
					  { 0, 0, 0, 0, 0 },
					  { 0, 0, 0, 0, 0 },
					  { 0, 0, 0, 0, 0 },
					  { 0, 0, 0, 0, 0 } };*/
	
	if (solveMazeUtil(maze, startx, starty, sol) == false) {
		cout << "Solution doesn't exist";
		return false;
	}
	changeArrayToChar(solu);
	printSolution(solu);
	return true;
}
bool checkstart(int x, int y, int maze[N][N]) {
	if ((x >= 0 && x <= N - 1) && (y >= 0 && y <= N - 1)) {
		cout << "Start hop le" << endl;
		return true;
	}
	else
	{
		cout << "Start khong hop le" << endl;
		return false;
	}
}
bool checkgoal(int x, int y, int maze[N][N])
{
	if ((x >= 0 && x <= N - 1) && (y >= 0 && y <= N - 1)) {
		cout << "Goal hop le" << endl;
		return true;
	}
	else
	{
		cout << "Goal khong hop le" << endl;
		return false;
	}
}
// A recursive utility function to solve Maze problem
bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N])
{
	// if (x, y is goal) return true
	if (x == goalx && y == goaly && maze[x][y] == 1) {
		sol[x][y] = 1;
		return true;
	}
	// Check if maze[x][y] is valid
	if (isSafe(maze, x, y) == true) {
		// Check if the current block is already part of
		// solution path.
		if (sol[x][y] == 1)
			return false;
		// mark x, y as part of solution path
		sol[x][y] = 1;
		/* Move forward in x direction */
		if (solveMazeUtil(maze, x + 1, y, sol) == true)
			return true;
		// If moving in x direction doesn't give solution
		// then Move down in y direction
		if (solveMazeUtil(maze, x, y + 1, sol) == true)
			return true;
		if (solveMazeUtil(maze, x - 1, y, sol) == true)
			return true;
		if (solveMazeUtil(maze, x, y - 1, sol) == true)
			return true;
		// If none of the above movements work then
		// BACKTRACK: unmark x, y as part of solution path
		sol[x][y] = 0;
		return false;
	}
	return false;
}

// driver program to test above function
int main()
{
	cout << "Nhap startx "; cin >> startx; cout << "Nhap starty "; cin >> starty;
	cout << "Nhap goalx "; cin >> goalx; cout << "Nhap goaly "; cin >> goaly;
	cout << "Start co x, y la " << startx << " " << starty << endl;
	cout << "Goal co x, y la " << goalx << " " << goaly << endl;
	int maze[N][N] = {{ 1, 1, 1, 1, 0, 1, 1 , 1 },
					  { 1, 0, 1, 1 ,0, 0, 0 , 1 },
					  { 1, 0, 1, 1 ,0, 1, 0 , 1 },
					  { 1, 0, 1, 1 ,0, 1, 1 , 1 },
					  { 1, 0, 1, 1 ,0, 1, 0 , 1 },
					  { 1, 1, 0, 1 ,0, 1, 0 , 1 },
					  { 1, 0, 1, 1 ,0, 1, 0 , 1 },
					  { 0, 0, 0, 1 ,1, 1, 0 , 1 }};
	checkstart(startx, starty, maze);
	checkgoal(goalx, goaly, maze);
	clock_t start, end;
	start = clock();
	solveMaze(maze);
	end = clock();
	double time_use = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Time to find the way: " << time_use;
	return 0;
}

// This code is contributed by Aditya Kumar (adityakumar129)

