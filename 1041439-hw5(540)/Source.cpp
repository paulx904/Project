#include <iostream>
#include <cstdio>
#include <list>
#include <iterator>
#include <list>
#include <string>
using namespace std;

int t;
int ele[1000000];   //記錄element所在的team.
list<int> lst;  //排队队列
list<int>::iterator team[1001]; //指向每個team在lst中排最後一個的元素的位置。若lst中没有team中的元素，則指向lst.end().

int main()
{
	int ca = 0;
	while (cin >> t && t)
	{
		lst.clear();
		int num, tmp;
		for (int i = 1; i <= t; ++i)
		{
			team[i] = lst.end();
			cin >> num;
			for (int j = 0; j < num; ++j)
			{
				cin >> tmp;
				ele[tmp] = i;
			}
		}
		cout << "Scenario #" << ++ca << endl;
		string s;
		while (cin >> s && s != "STOP")
		{
			if (s == "ENQUEUE")
			{
				cin >> tmp;
				if (team[ele[tmp]] != lst.end())
				{
					++team[ele[tmp]];
					team[ele[tmp]] = lst.insert(team[ele[tmp]], tmp);
				}
				else
				{
					team[ele[tmp]] = lst.insert(team[ele[tmp]], tmp);
				}
			}
			else if (s == "DEQUEUE")
			{
				int top = lst.front();
				if (team[ele[top]] == lst.begin())
				{
					team[ele[top]] = lst.end();
				}
				lst.pop_front();
				cout << top << endl;
			}
		}
		cout << endl;
	}
	system("pause");
	return 0;
}
