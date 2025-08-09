#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <set>
#define ll long long
using namespace std;
const ll MAXN = 10001;

// all subsequences of a string
void f(const string &s, ll i, string path, set<string> &ans)
{
    if (i == s.length())
    {
        ans.insert(path);
        return;
    }

    f(s, i + 1, path + s[i], ans);
    f(s, i + 1, path, ans);
}

vector<string> subsequences(string s)
{
    set<string> ans;
    string path = "";

    f(s, 0, path, ans);

    vector<string> result(ans.begin(), ans.end());
    return result;
}

signed main()
{
    string s = "abcd";
    vector<string> ss = subsequences(s);
    for (string sss : ss)
    {
        cout << sss << endl;
    }
}
