#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

struct position
{
	short x, y;
};

struct Info
{
	int type;
	position pos1;
	position pos2;
	position cen;
	float size;
};

int main()
{
	vector <Info> shapeList;
	while (true)
	{
		Info figure;
		char menu = NULL;
		int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		cout << "보관 중인 도형 개수: " << shapeList.size() << endl;
		cout << "choose menu (1:circle / 2:square / p:show all shape / q:quit) = ";
		cin >> menu;
		if ('1' != menu && '2' != menu && 'p' != menu && 'q' != menu && 'P' != menu && 'Q' != menu)
		{
			cout << "선택지 중에서만 선택해주세요\n";
			Sleep(1000);
			system("cls");
			continue;
		}
		else if ('1' == menu)
		{
			if (10 == shapeList.size())
			{
				cout << "List is full !\n";
				Sleep(1000);
				system("cls");
				continue;
			}
			cout << "choose points (x1 y1 x2 y2) = ";
			cin >> x1 >> y1 >> x2 >> y2;
			float r = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) / 2;
			figure.type = 1;
			figure.size = 3.14 * r * r;
			figure.pos1.x = x1;
			figure.pos2.x = x2;
			figure.pos1.y = y1;
			figure.pos2.y = y2;
			figure.cen.x = (x1 + x2) / 2;
			figure.cen.y = (y1 + y2) / 2;
			shapeList.push_back(figure);

			cout << "finish add shape!\n";
			Sleep(1000);
			system("cls");
		}
		else if ('2' == menu)
		{
			if (10 == shapeList.size())
			{
				"List is full !\n";
				Sleep(1000);
				continue;
			}
			cout << "choose points (x1 y1 x2 y2) = ";
			cin >> x1 >> y1 >> x2 >> y2;

			figure.type = 2;
			figure.size = abs(x2 - x1) * abs(y2 - y1);
			figure.pos1.x = x1;
			figure.pos2.x = x2;
			figure.pos1.y = y1;
			figure.pos2.y = y2;
			figure.cen.x = (x1 + x2) / 2;
			figure.cen.y = (y1 + y2) / 2;
			shapeList.push_back(figure);

			cout << "finish add shape!\n";
			Sleep(1000);
			system("cls");
		}
		else if ('p' == menu || 'P' == menu)
		{
			for (auto& iter : shapeList)
			{
				if (1 == iter.type)
					cout << "Circle\n";
				else
					cout << "Rect\n";
				cout << "두점 : " << iter.pos1.x << " , " << iter.pos1.y << " / " << iter.pos2.x << " , " << iter.pos2.y << endl;
				cout << "면적 : " << iter.size << endl;
				cout << "중심 : " << iter.cen.x << " , " << iter.cen.y << endl;
				cout << endl;
			}
		}
		else if ('q' == menu || 'Q' == menu)
		{
			exit(0);
		}
	}
}