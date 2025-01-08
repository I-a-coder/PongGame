#include <conio.h>
#include<windows.h>
#include<iostream>
using namespace std;
#define BLACK 0
#define BROWN 6
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9
void IncreaseConsoleFontSize(int increment) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);

	// Get the current console font information
	GetCurrentConsoleFontEx(hOut, FALSE, &cfi);

	// Increase the font size
	cfi.dwFontSize.X += increment;
	cfi.dwFontSize.Y += increment;

	// Set the new font size
	SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
}



void SetClr(int tcl, int bcl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}

char bar = 219;
char ball = 'O';
void gotoRowCol(int i, int j)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = j;
	scrn.Y = i;
	SetConsoleCursorPosition(hOuput, scrn);
}
//Phase 1
void print_board(int rows, int cols, int row1, int col1)
{
	char boarder = 219;
	cout << endl;
	for (int i = row1; i <= rows; i++)
	{
		for (int j = col1; j <= cols; j++)
		{
			if (i == row1 || i == rows)
			{
				gotoRowCol(i, j);
				cout << boarder;
			}
			else
			{
				if (j == col1 || j == cols)
				{
					gotoRowCol(i, j);
					cout << boarder;
				}
			}
		}
	}
}
void print_ball(int x, int y, char ball)
{
	gotoRowCol(x, y);
	cout << ball;
}
void move_ball(int& x, int& y, int direction)
{

	switch (direction)
	{

	case 1:
		x--;
		y--;//top left
		break;
	case 2:
		x--;
		y++;//top right
		break;
	case 3:
		x++;
		y--; //bottom left
		break;
	case 4:
		x++;
		y++; //bottom right
		break;
	case 5:
		y++; // right
		break;
	case 6:
		y--; // left
		break;

	}
}
void boundary_bounce(int x, int y, int& direction)
{
	if (x == 1 || x == 24)
	{

		int  previous_direction = direction;
		if (previous_direction == 1)
		{
			direction = 3;
		}
		if (previous_direction == 3)
		{
			direction = 1;
		}
		if (previous_direction == 2)
		{
			direction = 4;
		}
		if (previous_direction == 4)
		{
			direction = 2;
		}



	}
	else if (y == 1 || y == 109)
	{

		int  previous_direction = direction;
		if (previous_direction == 1)
		{
			direction = 2;
		}
		if (previous_direction == 2)
		{
			direction = 1;
		}
		if (previous_direction == 3)
		{
			direction = 4;
		}
		if (previous_direction == 4)
		{
			direction = 3;
		}
		if (previous_direction == 5)
		{
			direction = 6;
		}
		if (previous_direction == 6)
		{
			direction = 5;
		}

	}

}

////Phase 2


void drawPlayerBars(char bar, int xp1, int yp1)
{
	for (int i = 1; i <= 8; i++)
	{
		gotoRowCol(xp1, yp1);
		cout << bar << endl;
		xp1++;
	}
}

void movePlayerBar(int& xp1, int& yp1, int& xp2, int& yp2)
{
	char b = 219;
	if (_kbhit())
	{
		char input = (_getch());

		if ((input == 'Z') || (input == 'z') && (xp1 > 1)) //up
		{
			drawPlayerBars(' ', xp1, yp1);
			xp1--;
			drawPlayerBars(b, xp1, yp1);

		}
		if ((input == 'X') || (input == 'x') && (xp1 < 17))//down
		{
			drawPlayerBars(' ', xp1, yp1);
			xp1++;
			drawPlayerBars(b, xp1, yp1);

		}
		if (input == 72 && xp2 > 1)  //Up Arrow
		{
			drawPlayerBars(' ', xp2, yp2);
			xp2--;
			drawPlayerBars(b, xp2, yp2);


		}
		if (input == 80 && xp2 < 17)  //Down Arrow
		{

			drawPlayerBars(' ', xp2, yp2);
			xp2++;
			drawPlayerBars(b, xp2, yp2);

		}
	}
}

int check_hit_on_paddles(int x, int y, int xp1, int yp1)
{
	int collision = 0;
	if ((x >= xp1 && x < xp1 + 8) && (y == yp1))
	{
		collision = 1; // Collision occurred
	}
	else
	{
		collision = 0;
	}
	return collision;
}
void ballDeflectionByBar(int collision1, int collision2, int& direction, int x, int xp1, int xp2)
{
	if (collision1 == 1)
	{
		if ((x >= xp1 && x < xp1 + 3))
		{
			direction = 2;
			//top right
		}
		if ((x >= xp1 + 3 && x < xp1 + 5))
		{
			direction = 5;// right
		}
		if ((x >= xp1 + 5 && x < xp1 + 8))
		{
			direction = 4;
			//bottom right
		}
	}
	if (collision2 == 1)
	{
		if ((x >= xp2 && x < xp2 + 3))
		{
			direction = 1;
			//top left
		}
		if ((x >= xp2 + 3 && x < xp2 + 5))
		{
			direction = 6;// left
		}
		if ((x >= xp2 + 5 && x < xp2 + 8))
		{
			direction = 3;
			//bottom left
		}
	}

}
//Phase 3
void Name(string& Name1, string& Name2)
{
	gotoRowCol(12, 40);
	IncreaseConsoleFontSize(5);
	cout << "Enter Player1 Name: ";
	cin >> Name1;
	gotoRowCol(13, 40);
	cout << "Enter Player2 Name: ";
	cin >> Name2;
	system("cls");

}
void Score_detector(int& Score1, int& Score2, int y, string Name1, string Name2)
{

	SetClr(WHITE, BLACK);
	gotoRowCol(27, 5);
	cout << Name1 << ":" << Score1;
	gotoRowCol(27, 101);
	cout << Name2 << ":" << Score2;
	if (y == 1)
	{
		Score2++;

	}
	if (y == 109)
	{
		Score1++;

	}
}

void Game_over(int Score1, int Score2, bool& game_over, string Name1, string Name2)
{
	if (Score1 == 5)
	{
		game_over = true;
		system("CLS");
		gotoRowCol(13, 51);
		SetClr(RED, BLACK);
		cout << "GAME OVER  [" << Name1 << " WINS!!!]";
		Sleep(2000);
	}

	else if (Score2 == 5)
	{
		game_over = true;
		system("CLS");
		gotoRowCol(13, 51);
		SetClr(RED, BLACK);
		cout << "GAME OVER [" << Name2 << "WINS!!!]";
		Sleep(2000);
	}
}
int difficulty_level(int& difficulty)
{
	gotoRowCol(12, 40);
	SetClr(BROWN, BLACK);
	cout << "SELECT DIFFICULTY LEVEL!\n SILVER = 1 \n COPPER = 2 \n  GOLD = 3\n Level: ";
	cin >> difficulty;
	system("cls");
	return difficulty;

}

int main()
{
	string Name1, Name2;
	char ball = 'O';
	char bar = 219, part = 0;
	bool game_over = false;
	int x = 20, y = 15, direction = 3, xp1 = 3, yp1 = 3, xp2 = 3, yp2 = 107, Score1 = 0,
		Score2 = 0, difficulty = 1, rows = 25, cols = 110, row1 = 0, col1 = 0, Choice = 1;
	Name(Name1, Name2);
	difficulty_level(difficulty);
	SetClr(GREEN, BLACK);
	print_board(rows, cols, row1, col1);
	drawPlayerBars(bar, xp1, yp1);
	drawPlayerBars(bar, xp2, yp2);

	while (!game_over)
	{

		Score_detector(Score1, Score2, y, Name1, Name2);
		Game_over(Score1, Score2, game_over, Name1, Name2);
		SetClr(GREEN, BLACK);
		movePlayerBar(xp1, yp1, xp2, yp2);
		int collision1 = check_hit_on_paddles(x, y, xp1, 4);
		int collision2 = check_hit_on_paddles(x, y, xp2, 106);
		ballDeflectionByBar(collision1, collision2, direction, x, xp1, xp2);
		boundary_bounce(x, y, direction);
		print_ball(x, y, ' ');
		move_ball(x, y, direction);
		print_ball(x, y, ball);
		if (difficulty == 1)
		{
			Sleep(60);
		}
		if (difficulty == 2)
		{
			Sleep(40);
		}
		if (difficulty == 3)
		{
			Sleep(20);
		}

	}
	system("CLS");
	gotoRowCol(13, 51);
	SetClr(BROWN, BLACK);
	cout << "Restart or Not?\n Press 1 for YES and 0 for Exit\n Choice = ";
	cin >> Choice;
	if (Choice == 1)
	{
		system("cls");
		main();
	}
	else if (Choice == 0)
	{
		SetClr(RED, BLACK);
		cout << "YOU ARE EXITED";
		return 0;
	}

}