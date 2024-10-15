#include <bits/stdc++.h>
using namespace std;

void reorder(vector<int>& v, int recent)
{
int temp;
for (int i=0; i<v.size(); i++)
{
if (v[i] == recent)
{
for (int j=i+1; j<v.size(); j++)
{
temp = v[j-1];
v[j-1] = v[j];
v[j] = temp;
}
break;
}
}
}

int main()
{
vector<int> v;

int next;
while (v.size() != 3)
{
cin >> next;

if (find(v.begin(), v.end(), next) != v.end())

{
reorder(v, next);
}

else
{
v.push_back(next);
}
}

for (int i=0; i<v.size(); i++)
{
cout << v[i] << " ";
}
cout << endl;

int page;
while (cin >> page)
{
if (find(v.begin(), v.end(), page) != v.end())
{
cout<<"New order of the Frame (Last page is most

recently used) ";

reorder(v, page);
}

else
{
v.erase(v.begin(), v.begin()+1);
v.push_back(page);
}

for (int i=0; i<v.size(); i++)

{
cout << v[i] << " ";
}
cout << endl;
}

}
