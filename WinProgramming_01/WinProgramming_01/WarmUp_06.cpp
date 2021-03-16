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
		if (48 <= formula[i] && 57 >= formula[i]) // 상수일때
		{
			if (48 <= formula[i + 1] && 57 >= formula[i + 1]) // 두자리 상수일때
			{
				numbers[count_numb] = 10 * (formula[i] - 48) + (formula[i + 1] - 48); // 다음수도 상수면 2자리수로 저장
				count_numb++;
				i++; // 한 차례 추가로 넘김
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
		int finish_point = 0; // 실질적으로 문장이 끝난곳
		if (48 > sentence[0] || 57 < sentence[0]) // 첫 자리 기호로 시작할때
		{
			cout << "숫자로 시작해 주세요\n";
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
				cout << "한자리, 두자리 숫자만 입력하세요\n";
				count = -1;
				break;
			}

			if ((48 > sentence[i] && 57 < sentence[i]) && // 상수가 아니면서
				('+' != sentence[i] && '-' != sentence[i] && '*' != sentence[i] && '/' != sentence[i])) // 사칙연산도 아닐때
			{
				cout << "사칙연산과 숫자만 입력하세요\n";
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