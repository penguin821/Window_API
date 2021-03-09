#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	srand(time(NULL));
	char sentence[60];
	
	int finish_point = 0;

	while (true)
	{
		cout << "������ �Է��ϼ��� : ";
		cin.getline(sentence, 60);
		int count = 0;

		for (int i = 0; i < 60; i++)
		{
			if ('.' == sentence[i])
			{
				finish_point = i;
				count++;
			}
		}

		for (int i = finish_point + 1; i < 59; i++)
		{
			sentence[i] = ' ';
		}
		sentence[59] = NULL;

		if (0 == count)
		{
			cout << "������ ��ħǥ�� �����ּ���" << endl;
			Sleep(1000);
		}
		else
			break;
	}
	system("cls");
	while (true)
	{
		char menu = NULL;
		cout << "�Է��� ���� : " << sentence << endl;
		cout << "�޴��� ������ : ";
		cin >> menu;

		switch (menu)
		{
		case 'e':
		case 'E':
		{
			int save_e[60];
			int count = 0;
			for (int i = 0; i < finish_point; i++)
			{
				if ('e' == sentence[i] || 'E' == sentence[i])
				{
					save_e[count] = i; // e�� E�� �ִ� �ε��� ��ȣ ����
					count++;
				}
			}

			for (int i = 0; i < count; i++)
			{
				int before_space = 0;
				int after_space = 0;
				int point = save_e[i];
				while (true) // �ش� e �� ������ ���� ã��
				{
					if (' ' != sentence[point])
						point--;
					else
					{
						before_space = point + 1;
						break;
					}

					if (-1 == point)
					{
						before_space = point + 1;
						break;
					}
				}
				point = save_e[i];
				while (true) // �ش� e �� ������ ���� ã��
				{
					if (' ' != sentence[point])
						point++;
					else if ('.' == sentence[point])
					{
						after_space = point - 1;
						break;
					}
					else
					{
						after_space = point - 1;
						break;
					}
				}

				for (int j = before_space; j <= after_space; j++)
				{
					if (sentence[j] >= 97 && sentence[j] <= 122) // �ҹ����̸�
						sentence[j] -= 32;
				}
			}
		}
			break;
		case 'f':
		case 'F':
			for (char& i : sentence)
			{
				if (' ' == i || -52 == i)
				{
					int select = rand() % 4;
					if (0 == select)
						i = '@';
					else if (1 == select)
						i = '%';
					else if (2 == select)
						i = '#';
					else if (3 == select)
						i = '.';
				}
			}
			break;
		case 'l':
		case 'L':
		{
			int count = 0;
			for (int i = 0; i < finish_point; i++)
			{
				if (((' ' == sentence[i]) && (' ' != sentence[i - 1]) && (' ' != sentence[i + 1])) || // �ڽ��� ����, �յڴ� ����ƴ�
					((' ' == sentence[i]) && (' ' == sentence[i - 1]) && (' ' != sentence[i + 1]))) // �ڽŰ� �ڱ� ������ ����, ���Ĵ� �ܾ��϶�
					count++;
			}

			if (' ' == sentence[0])
				cout << "�ܾ��� ���� : " << count << endl;
			else
				cout << "�ܾ��� ���� : " << count + 1 << endl;
			break;
		}
		case 'c':
		case 'C':
			for (char& i : sentence)
			{
				if (i >= 65 && i <= 90)
					i += 32;
				else if (i >= 97 && i <= 122)
					i -= 32;
			}
			break;
		case 'q':
		case 'Q':
			exit(0);
			break;
		default:
			cout << "���� �޴��Դϴ�!" << endl;
		}
		cout << endl;
	}
	return 0;
}