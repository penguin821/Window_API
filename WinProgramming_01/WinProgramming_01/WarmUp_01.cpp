#include <iostream>
using namespace std;

int main()
{
	srand(time(NULL));

	int i_components[20];
	char c_components[20];
	int i_selected[4][5];
	char c_selected[4][5];
	short select = 0;
	char command = NULL;

	while (true)
	{
		cout << "select (1/2) : ";
		cin >> select;

		if (1 == select)
		{
			for (int i = 0; i < 20; i++)
			{
				i_components[i] = rand() % 50 + 1;
				for (int j = 0; j < i; j++)
				{
					if (i_components[i] == i_components[j])
					{
						i--;
						break;
					}
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					i_selected[i][j] = i_components[(5 * i) + j];
				}
			}

			while (true)
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						cout << i_selected[i][j] << "\t";
					}
					cout << endl;
				}

				cout << "choose command : ";
				cin >> command;

				if ('p' == command)
				{
					system("cls");
					break;
				}
				switch (command)
				{
				case 'a':
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							i_components[(5 * i) + j] = i_selected[i][j];
						}
					}

					for (int i = 0; i < 20; i++)
						for (int j = 0; j < 19; j++)
						{
							if (i_components[j] > i_components[j + 1])
							{
								int temp = i_components[j];
								i_components[j] = i_components[j + 1];
								i_components[j + 1] = temp;
							}
						}

					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							i_selected[i][j] = i_components[(5 * i) + j];
						}
					}
					cout << endl;
					break;
				case 'd':
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							i_components[(5 * i) + j] = i_selected[i][j];
						}
					}

					for (int i = 0; i < 20; i++)
						for (int j = 0; j < 19; j++)
						{
							if (i_components[j] > i_components[j + 1])
							{
								int temp = i_components[j];
								i_components[j] = i_components[j + 1];
								i_components[j + 1] = temp;
							}
						}

					for (int j = 0; j < 5; j++)
					{
						for (int i = 0; i < 4; i++)
						{
							i_selected[3 - i][j] = i_components[i + (4 * j)];
						}
					}
					cout << endl;
					break;
				case 't':
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							if (i_selected[i][j] % 2 == 1)
								i_selected[i][j] = 0;
						}
					}
					cout << endl;
					break;
				case 's':
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							if (i_selected[i][j] % 2 == 0)
								i_selected[i][j] = 0;
						}
					}
					cout << endl;
					break;
				case 'm':
				{
					int max = 0;
					int last_x, last_y;
					bool is_first = true;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							if (i_selected[i][j] > max)
							{
								if (true == is_first)
								{
									max = i_selected[i][j];
									last_x = i;
									last_y = j;
									is_first = false;
								}
								else
								{
									i_selected[last_x][last_y] = 0;
									max = i_selected[i][j];
									last_x = i;
									last_y = j;
								}
							}
							else
								i_selected[i][j] = 0;
						}
					}
				}
				cout << endl;
				break;
				case 'n':
				{
					int min = 50;
					int last_x, last_y;
					bool is_first = true;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							if (i_selected[i][j] < min)
							{
								if (true == is_first)
								{
									min = i_selected[i][j];
									last_x = i;
									last_y = j;
									is_first = false;
								}
								else
								{
									i_selected[last_x][last_y] = 0;
									min = i_selected[i][j];
									last_x = i;
									last_y = j;
								}
							}
							else
								i_selected[i][j] = 0;
						}
					}
				}
				cout << endl;
				break;
				case 'r':
				{
					for (int i = 0; i < 50; i++)
					{
						int temp[1][1] = {};
						int frand1 = rand() % 4;
						int frand2 = rand() % 5;

						int brand1 = rand() % 4;
						int brand2 = rand() % 5;

						if (frand1 != brand1 || frand2 != brand2)
						{
							temp[0][0] = i_selected[frand1][frand2];
							i_selected[frand1][frand2] = i_selected[brand1][brand2];
							i_selected[brand1][brand2] = temp[0][0];
						}
					}
				}
				cout << endl;
				break;
				case 'q':
					exit(0);
					break;
				default:
					cout << "No such command!\n";
					break;
				}
			}
		}
		else if (2 == select)
		{
			for (int i = 0; i < 20; i++)
			{
				int big_or_small = rand() % 2;
				if (0 == big_or_small)
					c_components[i] = rand() % 26 + 65; // 소문자
				else if (1 == big_or_small)
					c_components[i] = rand() % 26 + 97; // 대문자

				for (int j = 0; j < i; j++)
				{
					if (c_components[i] == c_components[j])
					{
						i--;
						break;
					}
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					c_selected[i][j] = c_components[(5 * i) + j];
				}
			}

			while (true)
			{
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						cout << c_selected[i][j] << "\t";
					}
					cout << endl;
				}

				cout << "choose command : ";
				cin >> command;

				if ('p' == command)
				{
					system("cls");
					break;
				}
				switch (command)
				{
				case 'a':
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							c_components[(5 * i) + j] = c_selected[i][j];
						}
					}

					for (int i = 0; i < 20; i++)
						for (int j = 0; j < 19; j++)
						{
							if (c_components[j] > c_components[j + 1])
							{
								int temp = c_components[j];
								c_components[j] = c_components[j + 1];
								c_components[j + 1] = temp;
							}
						}

					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							c_selected[i][j] = c_components[(5 * i) + j];
						}
					}
					cout << endl;
					break;
				case 'd':
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							c_components[(5 * i) + j] = c_selected[i][j];
						}
					}

					for (int i = 0; i < 20; i++)
						for (int j = 0; j < 19; j++)
						{
							if (c_components[j] > c_components[j + 1])
							{
								int temp = c_components[j];
								c_components[j] = c_components[j + 1];
								c_components[j + 1] = temp;
							}
						}

					for (int j = 0; j < 5; j++)
					{
						for (int i = 0; i < 4; i++)
						{
							c_selected[3 - i][j] = c_components[i + (4 * j)];
						}
					}
					cout << endl;
					break;
				case 't':
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							if (c_selected[i][j] % 2 == 1)
								c_selected[i][j] = '0';
						}
					}
					cout << endl;
					break;
				case 's':
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							if (c_selected[i][j] % 2 == 0)
								c_selected[i][j] = '0';
						}
					}
					cout << endl;
					break;
				case 'm':
				{
					int max = 0;
					int last_x, last_y;
					bool is_first = true;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							if (c_selected[i][j] > max)
							{
								if (true == is_first)
								{
									max = c_selected[i][j];
									last_x = i;
									last_y = j;
									is_first = false;
								}
								else
								{
									c_selected[last_x][last_y] = 0;
									max = c_selected[i][j];
									last_x = i;
									last_y = j;
								}
							}
							else
								c_selected[i][j] = 0;
						}
					}
				}
				cout << endl;
				break;
				case 'n':
				{
					int min = 50;
					int last_x, last_y;
					bool is_first = true;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							if (c_selected[i][j] < min)
							{
								if (true == is_first)
								{
									min = c_selected[i][j];
									last_x = i;
									last_y = j;
									is_first = false;
								}
								else
								{
									c_selected[last_x][last_y] = 0;
									min = c_selected[i][j];
									last_x = i;
									last_y = j;
								}
							}
							else
								c_selected[i][j] = 0;
						}
					}
				}
				cout << endl;
				break;
				case 'r':
				{
					for (int i = 0; i < 50; i++)
					{
						int temp[1][1] = {};
						int frand1 = rand() % 4;
						int frand2 = rand() % 5;

						int brand1 = rand() % 4;
						int brand2 = rand() % 5;

						if (frand1 != brand1 || frand2 != brand2)
						{
							temp[0][0] = c_selected[frand1][frand2];
							c_selected[frand1][frand2] = c_selected[brand1][brand2];
							c_selected[brand1][brand2] = temp[0][0];
						}
					}
				}
				cout << endl;
				break;
				case 'q':
					exit(0);
					break;
				default:
					cout << "No such command!\n";
					break;
				}
			}
		}
	}
	return 0;
}