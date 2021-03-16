#include <iostream>
using namespace std;

constexpr int MAX_MONTH = 12;
constexpr int WEEK = 7;

int Months[MAX_MONTH] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
char Days[WEEK][3] = { "��", "ȭ", "��", "��", "��", "��", "��" };

bool isLeapYear(int year) // ���� ���
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return true;
	else
		return false;
}

string findDay(int year, int month, int day) // ���� �������� ���
{
	int allDays = 0;
	int i = 0;
	for (i = 1900; i < year; i++)
	{
		if (isLeapYear(i))
			allDays += 366;
		else
			allDays += 365;
	}
	for (int j = 1; j < month; j++)
	{
		if (isLeapYear(i))
		{
			Months[1] = 29;
			allDays += Months[j - 1];
		}
		else
		{
			Months[1] = 28;
			allDays += Months[j - 1];
		}
	}
	allDays += day - 1;
	return Days[allDays % 7];
}

void calender(int year, int month, int day) // �޷� �׸���
{
	cout << year << "�� " << month << "�� " << day << "�� : " << findDay(year, month, day) << "\n";
	int start_date;
	// 2021�� 3�� 2�� ������
	for (int i = 0; i < WEEK; ++i)
	{
		if (findDay(year, month, 1) == Days[i])
		{
			start_date = i;
			break;
		}
	}
	if (isLeapYear(year))
		Months[1] = 29;
	else
		Months[1] = 28;

	for (int i = 0; i < WEEK; ++i)
	{
		cout << "     " << Days[(start_date + i) % 7] << "\t";
	}
	cout << "\n";
	for (int i = 1; i <= Months[month-1]; i++)
	{
		cout << "     " << i << "\t";
		if (0 == i % WEEK)
			cout << "\n";
	}
	cout << "\n";


}

int main()
{
	while (true)
	{
		int year = 0, month = 0, day = 0; // ������
		char menu = NULL;
		cout << "1: ���� �˻� �� �޷� ��� / f: 13���� �ݿ��� ��� = ";
		cin >> menu;
		if ('1' != menu && 'f' != menu)
			continue;
		switch (menu)
		{
		case '1':
		{
			cout << "�˻��� �� �� �� : ";
			cin >> year >> month >> day;
			if (2020 > year || 2030 < year)
				continue;
			if (1 > month || 12 < month)
				continue;
			if (1 > day || 31 < day)
				continue;
			calender(year, month, day);
		}
		break;
		case 'f':
		case 'F':
		{
			for (int i = 2020; i < 2031; i++)
			{
				for (int j = 1; j <= MAX_MONTH; j++)
				{
					if (isLeapYear(i))
						Months[1] = 29;
					else
						Months[1] = 28;

					for (int k = 1; k <= Months[j-1]; k++)
					{
						if (13 == k && "��" == findDay(i, j, k))
						{
							cout << i << "�� " << j << "�� " << k << "�� : "
								<< findDay(i, j, k) << "\n";
						}
					}
				}
			}
		}
		break;
		}
	}
}