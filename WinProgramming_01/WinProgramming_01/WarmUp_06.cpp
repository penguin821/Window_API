#include <iostream>
#include <Windows.h>
using namespace std;

constexpr int MAX_SIZE = 14;

float multiplication(float a, float b)
{
	return a * b;
}

float addition(float a, float b)
{
	return a + b;
}

float subtraction(float a, float b)
{
	return a - b;
}

float division(float a, float b)
{
	return a / b;
}

void make_formula(int end, char formula[])
{
	float numbers[MAX_SIZE];
	char signs[MAX_SIZE];
	int count_numb = 0;
	int count_sign = 0;
	for (int i = 0; i < end; i++)
	{
		if (48 <= formula[i] && 57 >= formula[i]) // ����϶�
		{
			if (48 <= formula[i + 1] && 57 >= formula[i + 1]) // ���ڸ� ����϶�
			{
				numbers[count_numb] = 10 * (formula[i] - 48) + (formula[i + 1] - 48); // �������� ����� 2�ڸ����� ����
				count_numb++;
				i++; // �� ���� �߰��� �ѱ�
			}
			else
			{
				numbers[count_numb] = formula[i] - 48;
				count_numb++;
			}
		}

		if ('+' == formula[i] || '-' == formula[i] ||
			'*' == formula[i] || '/' == formula[i])
		{
			signs[count_sign] = formula[i];
			count_sign++;
		}
	}

	for (int i = 0; i < count_sign; i++)
	{
		cout << numbers[i] << " " << signs[i] << " ";
	}
	cout << numbers[count_numb - 1] << " = ";

	for (int i = 0; i < count_sign; i++)
	{
		if ('*' == signs[i])
		{
			numbers[i] = multiplication(numbers[i], numbers[i + 1]);
			numbers[i + 1] = numbers[i];

			int j = i;
			while ('*' == signs[j - 1] || '/' == signs[j - 1])
			{
				numbers[j - 1] = numbers[j];
				j--;
			}
		}
		if ('/' == signs[i])
		{
			numbers[i] = division(numbers[i], numbers[i + 1]);
			numbers[i + 1] = numbers[i];

			int j = i;
			while ('*' == signs[j - 1] || '/' == signs[j - 1])
			{
				numbers[j - 1] = numbers[j];
				j--;
			}
		}
	}
	int last_sign_pos = 0;
	for (int i = 0; i < count_sign; i++)
	{
		if ('+' == signs[i])
		{
			numbers[i] = addition(numbers[i], numbers[i + 1]);
			numbers[i + 1] = numbers[i];

			int j = i;
			while ('*' == signs[j - 1] || '/' == signs[j - 1])
			{
				numbers[j - 1] = numbers[j];
				j--;
			}
			j = i;
			while ('*' == signs[j + 1] || '/' == signs[j + 1])
			{
				numbers[j + 2] = numbers[j + 1];
				j++;
			}
			last_sign_pos = i + 1;
		}
		if ('-' == signs[i])
		{
			numbers[i] = subtraction(numbers[i], numbers[i + 1]);
			numbers[i + 1] = numbers[i];

			int j = i;
			while ('*' == signs[j - 1] || '/' == signs[j - 1])
			{
				numbers[j - 1] = numbers[j];
				j--;
			}
			j = i;
			while ('*' == signs[j + 1] || '/' == signs[j + 1])
			{
				numbers[j + 2] = numbers[j + 1];
				j++;
			}
			last_sign_pos = i + 1;
		}
	}
	cout << numbers[last_sign_pos];
}

int main()
{
	while (true)
	{
		char sentence[MAX_SIZE];
		cin.getline(sentence, MAX_SIZE);
		int finish_point = 0; // ���������� ������ ������
		if (48 > sentence[0] || 57 < sentence[0]) // ù �ڸ� ��ȣ�� �����Ҷ�
		{
			cout << "���ڷ� ������ �ּ���\n";
			continue;
		}
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if ('\0' == sentence[i])
				finish_point = i;
		}

		int count = 0;

		for (int i = 0; i < finish_point; i++)
		{
			if (48 <= sentence[i] && 57 >= sentence[i])
				count++;
			else
				count = 0;

			if (3 <= count)
			{
				cout << "���ڸ�, ���ڸ� ���ڸ� �Է��ϼ���\n";
				count = -1;
				break;
			}

			if ((48 > sentence[i] && 57 < sentence[i]) && // ����� �ƴϸ鼭
				('+' != sentence[i] && '-' != sentence[i] && '*' != sentence[i] && '/' != sentence[i])) // ��Ģ���굵 �ƴҶ�
			{
				cout << "��Ģ����� ���ڸ� �Է��ϼ���\n";
				count = -1;
				break;
			}
		}

		if (-1 != count || 3 <= count)
		{
			make_formula(finish_point, sentence);
			return 0;
		}
	}
	return 0;
}