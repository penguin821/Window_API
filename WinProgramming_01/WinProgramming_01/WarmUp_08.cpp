#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	while (true)
	{
		int shape, size;
		cout << "모양(1-X, 2-역삼각, 3-마름모, 4-나비, 5-모래시계, 6-테두리 사각형)과 넓이(짝수) 기입: ";
		cin >> shape >> size;

		if (1 > shape || 6 < shape)
			continue;
		if (1 == size % 2 || 40 < size)
			continue;

		int height = size / 2;
		switch (shape)
		{
		case 1:
			if (height % 2 == 1)
			{
				for (float i = 0; i < ceil(height / 2); i++)
				{
					for (float j = 0; j < i * 2; j++)
					{
						cout << " ";
					}
					for (float j = 0; j < size - (i * 4); j++)
					{
						if (0 == j || size - (i * 4) - 1 == j)
							cout << "*";
						else
							cout << " ";
					}
					cout << "\n";
				}

				for (int i = 0; i < height - ceil(height / 2); i++)
				{
					for (int j = 0; j < height - (i * 2) - 1; j++)
					{
						cout << " ";
					}
					for (int j = 0; j < (i * 4) + 2; j++)
					{
						if (0 == j || (i * 4) + 2 - 1 == j)
							cout << "*";
						else
							cout << " ";
					}
					cout << "\n";
				}
			}
			else
			{
				for (float i = 0; i < ceil(height / 2); i++)
				{
					for (float j = 0; j < i * 2; j++)
					{
						cout << " ";
					}
					for (float j = 0; j < size - (i * 4); j++)
					{
						if (0 == j || size - (i * 4) - 1 == j)
							cout << "*";
						else
							cout << " ";
					}
					cout << "\n";
				}

				for (int i = 0; i < height - ceil(height / 2); i++)
				{
					for (int j = 0; j < height - (i * 2) - 2; j++)
					{
						cout << " ";
					}
					for (int j = 0; j < (i * 4) + 4; j++)
					{
						if (0 == j || (i * 4) + 4 - 1 == j)
							cout << "*";
						else
							cout << " ";
					}
					cout << "\n";
				}
			}
			break;
		case 2:
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < i ; j++)
				{
					cout << " ";
				}
				for (int j = 0; j < size - (i * 2); j++)
				{
					cout << "*";
				}
				cout << "\n";
			}
			break;
		case 3:
			for (int i = 0; i < height; i++)
			{
				for (int j = height - 1; j > i; j--)
				{
					cout << " ";
				}
				for (int j = 0; j < 2 * i + 2; j++)
				{
					cout << "*";
				}
				cout << "\n";
			}
			for (int i = 1; i < height; i++)
			{
				for (int j = 0; j < i; j++)
				{
					cout << " ";
				}
				for (int j = 2 * height; j > 2 * i; j--)
				{
					cout << "*";
				}
				cout << "\n";
			}
			break;
		case 4:
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j <= i; j++)
					cout << "*";
				for (int x = 1; x < height - i; x++)
					cout << " ";
				for (int y = 1; y < height - i; y++)
					cout << " ";
				for (int z = 0; z <= i; z++)
					cout << "*";
				cout << "\n";
			}
			for (int i = 1; i < height; i++)
			{
				for (int j = 0; j < height - i; j++)
					cout << "*";
				for (int x = 1; x <= i; x++)
					cout << " ";
				for (int y = 1; y <= i; y++)
					cout << " ";
				for (int z = 0; z < height - i; z++)
					cout << "*";
				cout << "\n";
			}
			break;
		case 5:
			if (height % 2 == 1)
			{
				for (float i = 0; i < ceil(height / 2); i++)
				{
					for (float j = 0; j < i * 2; j++)
					{
						cout << " ";
					}
					for (float j = 0; j < size - (i * 4); j++)
					{
						cout << "*";
					}
					cout << "\n";
				}

				for (int i = 0; i < height- ceil(height / 2); i++)
				{
					for (int j = 0; j < height - (i*2) - 1; j++)
					{
						cout << " ";
					}
					for (int j = 0; j < (i * 4) + 2; j++)
					{
						cout << "*";
					}
					cout << "\n";
				}
			}
			else
			{
				for (float i = 0; i < ceil(height / 2); i++)
				{
					for (float j = 0; j < i * 2; j++)
					{
						cout << " ";
					}
					for (float j = 0; j < size - (i * 4); j++)
					{
						cout << "*";
					}
					cout << "\n";
				}

				for (int i = 0; i < height - ceil(height / 2); i++)
				{
					for (int j = 0; j < height - (i * 2) - 2; j++)
					{
						cout << " ";
					}
					for (int j = 0; j < (i * 4) + 4; j++)
					{
						cout << "*";
					}
					cout << "\n";
				}
			}
			break;
		case 6:
			for (int i = 0; i < height; i++)
			{
				if (0 == i || height - 1 == i)
				{
					for (int j = 0; j < size; j++)
					{
						cout << "*";
					}
				}
				else
				{
					for (int j = 0; j < size; j++)
					{
						if (0 == j || size - 1 == j)
							cout << "*";
						else
							cout << " ";
					}
				}
				cout << "\n";
			}
			break;
		}
	}

}

/* 정삼각형
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < height - i - 1; j++)
				{
					cout << " ";
				}
				for (int j = 0; j < i * 2 + 2; j++)
				{
					cout << "*";
				}
				cout << "\n";
			}
*/