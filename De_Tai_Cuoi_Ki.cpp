// De_Tai_Cuoi_Ki.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <string>
#include <glut.h>

// C++ program to solve Rat in a Maze problem using
// backtracking

using namespace std;
// Maze size
#define N 5

int sol[N][N];

bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]);

// A utility function to print solution matrix sol[N][N]
void printSolution(int sol[N][N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << " " << sol[i][j] << " ";
		cout << endl;
	}
}

void printMaze(int maze[N][N]) {
	for (int i = 0; i < 2 * N; ++i) {
		cout << "_";
	}
	cout << endl;
	for (int i = 0; i < N; ++i) {
		cout << "|";
		for (int j = 0; j < N; ++j) {
			/*int c = maze[i][j];*/
			cout << ((maze[i+1][j] == 1 && maze[i][j]) ? " " : "_");
			if (maze[i][j+1] == 1 && maze[i][j])
				cout << " ";
			else cout << "|";
		}
		cout << endl;
	}
}
//int maze[N][N] = {	{ 1, 1, 0, 0, 0 },
//						{ 0, 1, 0, 1, 0 },
//						{ 1, 1, 1, 0, 0},
//						{ 1, 0, 0, 1, 0},
//						{ 1, 1, 1, 1, 1} };

//void printSolution(string solu[N][N])
//{
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++)
//			cout << " " << solu[i][j] << " ";
//		cout << endl;
//	}
//}

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
	/*string solu[N][N];*/
	/*scanSolution(maze, solu);*/
	int sol[N][N] = { { 0, 0, 0, 0, 0 },
					  { 0, 0, 0, 0, 0 },
					  { 0, 0, 0, 0, 0 },
					  { 0, 0, 0, 0, 0 },
					  { 0, 0, 0, 0, 0 } };
	
	if (solveMazeUtil(maze, 0, 0, sol) == false) {
		cout << "Solution doesn't exist";
		return false;
	}
	/*changeArrayToChar(solu);*/
	/*printSolution(sol);*/
	printMaze(sol);
	return true;
}

// A recursive utility function to solve Maze problem
bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N])
{
	// if (x, y is goal) return true
	if (x == N - 1 && y == N - 1 && maze[x][y] == 1) {
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
	int maze[N][N] = {  { 1, 1, 0, 1, 0 },
						{ 0, 1, 1, 1, 0 },
						{ 1, 1, 1, 0, 0},
						{ 1, 0, 0, 1, 0}, 
						{ 1, 1, 1, 1, 1} };
	cout << "Maze:" << endl;
	printMaze(maze);
	clock_t start, end;
	start = clock();
	cout << "Solution:" << endl;
	solveMaze(maze);
	end = clock();
	double time_use = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Time to find the way: " << time_use;
	
	return 0;
}


//#include<iostream>
//using namespace std;
//int rx = 100, ry = 125;
//int xCenter = 250, yCenter = 250;
//#define GL_PROJECTION 0x1701
//#define GL_POINTS 0x0000
//
//void myinit(void)
//{
//    glClearColor(1.0, 1.0, 1.0, 0.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
//}
//
//void setPixel(GLint x, GLint y)
//{
//    glBegin(GL_POINTS);
//    glVertex2i(x, y);
//    glEnd();
//}
//void ellipseMidPoint()
//{
//    float x = 0;
//    float y = ry;
//    float p1 = ry * ry - (rx * rx) * ry + (rx * rx) * (0.25);
//    float dx = 2 * (ry * ry) * x;
//    float dy = 2 * (rx * rx) * y;
//    glColor3ub(rand() % 255, rand() % 255, rand() % 255);
//    while (dx < dy)
//    {
//        setPixel(xCenter + x, yCenter + y);
//        setPixel(xCenter - x, yCenter + y);
//        setPixel(xCenter + x, yCenter - y);
//        setPixel(xCenter - x, yCenter - y);
//        if (p1 < 0)
//        {
//            x = x + 1;
//            dx = 2 * (ry * ry) * x;
//            p1 = p1 + dx + (ry * ry);
//        }
//        else
//        {
//            x = x + 1;
//            y = y - 1;
//            dx = 2 * (ry * ry) * x;
//            dy = 2 * (rx * rx) * y;
//            p1 = p1 + dx - dy + (ry * ry);
//        }
//    }
//    glFlush();
//
//    float p2 = (ry * ry) * (x + 0.5) * (x + 0.5) + (rx * rx) * (y
//        - 1) * (y - 1) - (rx * rx) * (ry * ry);
//    glColor3ub(rand() % 255, rand() % 255, rand() % 255);
//    while (y > 0)
//    {
//        setPixel(xCenter + x, yCenter + y);
//        setPixel(xCenter - x, yCenter + y);
//        setPixel(xCenter + x, yCenter - y);
//        setPixel(xCenter - x, yCenter - y);
//        if (p2 > 0)
//        {
//            x = x;
//            y = y - 1;
//            dy = 2 * (rx * rx) * y;
//            p2 = p2 - dy + (rx * rx);
//        }
//        else
//        {
//            x = x + 1;
//            y = y - 1;
//            dy = dy - 2 * (rx * rx);
//            dx = dx + 2 * (ry * ry);
//            p2 = p2 + dx -
//                dy + (rx * rx);
//        }
//    }
//    glFlush();
//}
//void display()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(1.0, 0.0, 0.0);
//    glPointSize(2.0);
//    ellipseMidPoint();
//    glFlush();
//}
//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    glutInitWindowSize(640, 480);
//    glutInitWindowPosition(10, 10);
//    glutCreateWindow("User_Name");
//    myinit();
//    glutDisplayFunc(display);
//    glutMainLoop();
//    return 0;
//}

