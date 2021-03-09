#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int Discriminate_Anagram(string s1, string s2)
{
	int count1 = 0;
	int count2 = 0;
	for (auto& s : s1)
	{
		if (' ' != s)
			count1++;
	}
	for (auto& s : s2)
	{
		if (' ' != s)
			count2++;
	}

	if (count1 != count2)
	{
		cout << "no anagram!\n";
		return 0;
	}
	else
	{
		string s1_sort = s1;
		string s2_sort = s2;

		sort(s1.begin(), s1.end());
		sort(s2.begin(), s2.end());

		auto iter1 = s1.begin();
		for (; iter1 != s1.end();)
		{
			if (' ' == *iter1)
				iter1 = s1.erase(iter1);
			else
				iter1++;
		}

		auto iter2 = s2.begin();
		for (; iter2 != s2.end();)
		{
			if (' ' == *iter2)
				iter2 = s2.erase(iter2);
			else
				iter2++;
		}

		//cout << s1 << endl;
		//cout << s2 << endl;

		if (s1 == s2)
		{
			cout << "result: '" << s1_sort << "' and '" << s2_sort << "' are anagram!\n";
			return 0;
		}
	}


}

int main()
{
	string anagram1;
	string anagram2;

	cout << "첫번째 문장 입력 : ";
	getline(cin,anagram1);
	cout << "두번째 문장 입력 : ";
	getline(cin,anagram2);

	Discriminate_Anagram(anagram1, anagram2);
}