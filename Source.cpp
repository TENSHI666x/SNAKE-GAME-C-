#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <random>
//MY FIRST SUPER (GAME) PROJECT FOR GIT))) I HAVE MANY BUGS HERE

bool gameOver;
const int width = 29; // Ширина width;
const int height = 15; // Высота height;
int x, y, fruitX, fruitY, scoreGame;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	gameOver = false; //Игра изначально не завершена;
	dir = STOP;
	x = (width / 2) - 1;
	y = (height / 2) - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	scoreGame = 0;
}

void Draw()
{
	system("cls"); //system ("clear") = linux; Очистка консоли для игры;
	for (int i = 0; i < width + 1; i++) //Вверхяя граница;
		std::cout << "#";
	std::cout << std::endl;

	for (int i = 0; i < height; i++) //Боковые границы;
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				std::cout << "#";
			if (i == y && j == x)
				std::cout << "@";
			else if (i == fruitY && j == fruitX)
				std::cout << "*";
			else 
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						std::cout << "o";
					}
				}
				if (!print)
					std::cout << " ";
			}
			
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width + 1; i++) //Нижняя граница;
		std::cout << "#";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "SCORE: " << scoreGame;
}

void Input()
{
	if (_kbhit()) {
		switch (_getch ())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'A':
			dir = LEFT;
			break;
		case 'W':
			dir = UP;
			break;
		case 'S':
			dir = DOWN;
			break;
		case 'D':
			dir = RIGHT;
			break;
		case 'G':
			gameOver = true;
			break;
		case 'g':
			gameOver = true;
			break;
		}
	}
}

void Physichs()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0)
	//gameOver = true;
	if (x >= width-1)
		x = 0;
	else if (x < 0)
		x = width-2;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height;


	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}


	if (x == fruitX && y == fruitY)
	{
		scoreGame++;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
	
}


int main() {
	
	Setup();
	while (!gameOver)
	{
		Sleep(60);
		Draw();
		Input();
		Physichs();
	}

	return 0;
}