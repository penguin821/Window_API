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
		cout << "문장을 입력하세요 : ";
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
			cout << "문장을 마침표로 마쳐주세요" << endl;
			Sleep(1000);
		}
		else
			break;
	}
	system("cls");
	while (true)
	{
		char menu = NULL;
		cout << "입력한 문장 : " << sentence << endl;
		cout << "메뉴를 고르세요 : ";
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
					save_e[count] = i; // e나 E가 있는 인덱스 번호 저장
					count++;
				}
			}

			for (int i = 0; i < count; i++)
			{
				int before_space = 0;
				int after_space = 0;
				int point = save_e[i];
				while (true) // 해당 e 뒤 마지막 공백 찾기
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
				while (true) // 해당 e 뒤 마지막 공백 찾기
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
					if (sentence[j] >= 97 && sentence[j] <= 122) // 소문자이면
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
				if (((' ' == sentence[i]) && (' ' != sentence[i - 1]) && (' ' != sentence[i + 1])) || // 자신은 공백, 앞뒤는 공백아님
					((' ' == sentence[i]) && (' ' == sentence[i - 1]) && (' ' != sentence[i + 1]))) // 자신과 자기 이전은 공백, 이후는 단어일때
					count++;
			}

			if (' ' == sentence[0])
				cout << "단어의 개수 : " << count << endl;
			else
				cout << "단어의 개수 : " << count + 1 << endl;
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
			cout << "없는 메뉴입니다!" << endl;
		}
		cout << endl;
	}
	return 0;
}