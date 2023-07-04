#include <iostream>
#include "console.h"
using namespace std;

const int ROWS = 20, COLS = 80;
int Field[ROWS][COLS];
int SnakeCount = 0;


/*class Snake {
public:
	int HeadX, HeadY;
	int DirX = 0, DirY = -1;
	Snake() {}
	Snake(int x, int y) : HeadX(x), HeadY(y) {}
	bool step() {
		*Next = Field[HeadY][HeadX] + 1;
	}
};

Snake* Snakes;
int SnakeCount = 0;

void InitSnake(Snake newValue) {
	int size = SnakeCount;
	Snake* arr = Snakes;
	int index = SnakeCount;
	Snake* newArr = new Snake[size + 1];
	for (size_t i = 0; i < size; i++)
	{
		newArr[i] = arr[i];
	}
	for (int i = size - 1; i >= index; i--)
	{
		swap(newArr[i], newArr[i + 1]);
	}
	newArr[index] = newValue;
	size++;
	delete[] arr;
	arr = newArr;
}*/

enum Objects
{
	Tail = 0,
	Apple = -1,
	Border = -2
};

int HeadX, HeadY;
int DirX = 0, DirY = -1;

void CreateSnake(int x, int y, int length) {
	HeadX = x;
	HeadY = y;
	for (int i = 0; i < length; i++)
	{
		Field[y + i][x] = length - i;
	}
}

int RandIn(int a, int b) {
	return (rand() % (b - a + 1)) + a;
}

void CreateApple() {
	int x, y;
	do
	{
		x = RandIn(0, COLS);
		y = RandIn(0, ROWS);
	} while (Field[y][x] != 0);
	Field[y][x] = -1;
}

bool Step() {
	int* Next = &Field[HeadY + DirY][HeadX + DirX];
	if (*Next == Apple) {
		*Next = Field[HeadY][HeadX] + 1;
		CreateApple();
		HeadX += DirX;
		HeadY += DirY;
		return true;
	}
	if (*Next == Border || *Next > 0)
	{
		return false;
	}
	*Next = Field[HeadY][HeadX] + 1;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
			if (Field[i][j] > 0) Field[i][j]--;
	}
	HeadX += DirX;
	HeadY += DirY;
	return true;
}



void fillField() {
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++) {
			Field[i][j] = 0;
		}
	}
}

ConsoleColor Colors[3];
ConsoleColor HeadColor = Green;
ConsoleColor DefaultColor = Black;

void Display() {
	ConsoleColor col;
	SetCursorPosition(0, 0);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++) {
			if (i == HeadY && j == HeadX) {
				col = HeadColor;
				SetColor(col, col);
				cout << " ";
				continue;
			}
			if (Field[i][j] > 0) { 
				col = White;//Colors[-Tail];
				SetColor(col, Black);
				cout << "x";
				continue;
			}
			if (Field[i][j] < 0) {
				col = Colors[-Field[i][j]];
			}
			else col = DefaultColor;
			SetColor(col, col);
			cout << " ";
		}
		cout << endl;
	}
}

void CreateBorder() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (i == 0 || 
				i == ROWS - 1 || 
				j == 0 || 
				j == COLS - 1) 
				Field[i][j] = -2;
			if (j % 20 == 0 && i > ROWS / 2) Field[i][j] = -2;
			if ((j - 10) % 20 == 0 && i < ROWS / 2) Field[i][j] = -2;
		}
	}
}

int main()
{
	srand(time(NULL));
	ShowConsoleCursor(false);
	Colors[-Tail] = White;
	Colors[-Apple] = Yellow;
	Colors[-Border] = Red;
	
	fillField();
	CreateSnake(15, 10, 3);
	CreateBorder();
	CreateApple();
	do
	{
		Display();
		Sleep(100);
		switch (getKey()) {
		case UP_ARROW:
			DirX = 0;
			DirY = -1;
			break;
		case DOWN_ARROW:
			DirX = 0;
			DirY = 1;
			break;
		case LEFT_ARROW:
			DirX = -1;
			DirY = 0;
			break;
		case RIGHT_ARROW:
			DirX = 1;
			DirY = 0;
			break;
		}
	} while (Step());
}
