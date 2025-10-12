#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <numeric>
#include <unordered_map>
#define ll long long
using namespace std;
using vl = vector<ll>;

void solve()
{
    string s;
    cin >> s;
    ll n = s.length();
    ll i = n - 1;
    while (i >= 0 && s[i] == '0')
    {
        i--;
    }
    ll cnt = 0;
    while (i >= 0)
    {
        if (s[i] == '0')
        {
            cnt++;
        }
        i--;
    }
    cout << n - cnt - 1 << endl;
}
signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}