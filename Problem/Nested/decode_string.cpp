#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#define ll long long
using namespace std;

ll where;

string get(ll cur, string s)
{
    string ans = "";
    while (cur--)
    {
        ans += s;
    }
    return ans;
}

string f(ll i, const string &s)
{
    string path = "";
    ll cur = 0;

    while (i < s.length() && s[i] != ']')
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            path += s[i++];
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            cur = cur * 10 + s[i++] - '0';
        }
        else
        {
            path += get(cur, f(i + 1, s));
            i = where + 1;
            cur = 0;
        }
    }

    where = i;
    return path;
}

string decoder(const string &exp)
{
    return f(0, exp);
}

signed main()
{
    cout << decoder("3[acb7[AB3[X]]]") << endl;
    return 0;
}