#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#define ll long long
using namespace std;

ll where;

void fill(map<string, ll> &atom, map<string, ll> pre, string name, ll cnt)
{
    if (name.size() > 0 || !pre.empty())
    {
        cnt = (cnt == 0 ? 1 : cnt);
        if (name.size() > 0)
        {
            atom[name] += cnt;
        }
        else
        {
            for (pair<string, ll> p : pre)
            {
                atom[p.first] += (cnt * p.second);
            }
        }
    }
}

map<string, ll> f(ll i, const string &s)
{
    map<string, ll> atom;

    string name = "";
    ll cnt = 0;
    map<string, ll> pre;

    while (i < s.length() && s[i] != ')')
    {
        if (s[i] == '(' || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            fill(atom, pre, name, cnt);
            name = "";
            cnt = 0;
            pre.clear();

            if (s[i] >= 'A' && s[i] <= 'Z')
            {
                name += s[i++];
            }
            else
            {
                pre = f(i + 1, s);
                i = where + 1;
            }
        }
        else if (s[i] >= 'a' && s[i] <= 'z')
        {
            name += s[i++];
        }
        else
        {
            cnt = cnt * 10 + s[i++] - '0';
        }
    }
    fill(atom, pre, name, cnt);

    where = i;
    return atom;
}

map<string, ll> atoms(const string &exp)
{
    return f(0, exp);
}

signed main()
{
    map<string, ll> mp = atoms("K4(ON(SO3)2)2");
    for (pair<string, ll> p : mp)
    {
        cout << p.first << ": " << p.second << endl;
    }
    return 0;
}