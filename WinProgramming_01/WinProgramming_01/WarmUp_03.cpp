#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

#define WORLD_SIZE 10

struct player
{
	short now_x, now_y;
	short last_x, last_y;
	char last_key;
};

int main()
{
	player p1 = { 0,0,0,0,NULL };
	player p2 = { 9,9,9,9,NULL };

	while (true)
	{
		for (int i = 0; i < WORLD_SIZE; ++i)
		{
			for (int j = 0; j < WORLD_SIZE; ++j)
			{
				if (p1.now_x == i && p1.now_y == j)
					cout << "★";
				else if (p2.now_x == i && p2.now_y == j)
					cout << "☆";
				else
					cout << "┿ ";
			}
			cout << endl;
		}
		cout << "p1 now : " << p1.now_x << "," << p1.now_y << " / last : " << p1.last_x << "," << p1.last_y << endl;
		cout << "p1 : " << p1.last_key << " / p2 : " << p2.last_key << endl;
		char order = _getch();
		switch (order)
		{
		case 'w':
		case 'W':
			p1.last_x = p1.now_x;
			p1.last_y = p1.now_y;
			if (p1.now_x == 0)
				p1.now_x = WORLD_SIZE - 1;
			else
				p1.now_x -= 1;
			p1.last_key = order;

			if ((p1.now_x == p2.now_x) && (p1.now_y == p2.now_y))
			{
				Beep(400, 500);
				p2.now_x = p1.last_x;
				p2.now_y = p1.last_y;
			}
			break;
		case 'a':
		case 'A':
			p1.last_x = p1.now_x;
			p1.last_y = p1.now_y;
			if (p1.now_y == 0)
				p1.now_y = WORLD_SIZE - 1;
			else
				p1.now_y -= 1;
			p1.last_key = order;
			if ((p1.now_x == p2.now_x) && (p1.now_y == p2.now_y))
			{
				Beep(400, 500);
				p2.now_x = p1.last_x;
				p2.now_y = p1.last_y;
			}
			break;
		case 's':
		case 'S':
			p1.last_x = p1.now_x;
			p1.last_y = p1.now_y;
			if (p1.now_x == WORLD_SIZE - 1)
				p1.now_x = 0;
			else
				p1.now_x += 1;
			p1.last_key = order;
			if ((p1.now_x == p2.now_x) && (p1.now_y == p2.now_y))
			{
				Beep(400, 500);
				p2.now_x = p1.last_x;
				p2.now_y = p1.last_y;
			}
			break;
		case 'd':
		case 'D':
			p1.last_x = p1.now_x;
			p1.last_y = p1.now_y;
			if (p1.now_y == WORLD_SIZE - 1)
				p1.now_y = 0;
			else
				p1.now_y += 1;
			p1.last_key = order;
			if ((p1.now_x == p2.now_x) && (p1.now_y == p2.now_y))
			{
				Beep(400, 500);
				p2.now_x = p1.last_x;
				p2.now_y = p1.last_y;
			}
			break;
		case 'i':
		case 'I':
			p2.last_x = p2.now_x;
			p2.last_y = p2.now_y;
			if (p2.now_x == 0)
				p2.now_x = WORLD_SIZE - 1;
			else
				p2.now_x -= 1;
			p2.last_key = order;
			if ((p1.now_x == p2.now_x) && (p1.now_y == p2.now_y))
			{
				Beep(400, 500);
				p1.now_x = p2.last_x;
				p1.now_y = p2.last_y;
			}
			break;
		case 'j':
		case 'J':
			p2.last_x = p2.now_x;
			p2.last_y = p2.now_y;
			if (p2.now_y == 0)
				p2.now_y = WORLD_SIZE - 1;
			else
				p2.now_y -= 1;
			p2.last_key = order;
			if ((p1.now_x == p2.now_x) && (p1.now_y == p2.now_y))
			{
				Beep(400, 500);
				p1.now_x = p2.last_x;
				p1.now_y = p2.last_y;
			}
			break;
		case 'k':
		case 'K':
			p2.last_x = p2.now_x;
			p2.last_y = p2.now_y;
			if (p2.now_x == WORLD_SIZE - 1)
				p2.now_x = 0;
			else
				p2.now_x += 1;
			p2.last_key = order;
			if ((p1.now_x == p2.now_x) && (p1.now_y == p2.now_y))
			{
				Beep(400, 500);
				p1.now_x = p2.last_x;
				p1.now_y = p2.last_y;
			}
			break;
		case 'l':
		case 'L':
			p2.last_x = p2.now_x;
			p2.last_y = p2.now_y;
			if (p2.now_y == WORLD_SIZE - 1)
				p2.now_y = 0;
			else
				p2.now_y += 1;
			p2.last_key = order;
			if ((p1.now_x == p2.now_x) && (p1.now_y == p2.now_y))
			{
				Beep(400, 500);
				p1.now_x = p2.last_x;
				p1.now_y = p2.last_y;
			}
			break;
			break;
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			cout << "그런 명령어는 없습니다!";
			Sleep(1000);
			break;
		}



		system("cls");
	}
}