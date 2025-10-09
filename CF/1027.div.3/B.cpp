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
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    ll ct0 = 0, ct1 = 0;
    for (ll i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            ct1++;
        }
        else
        {
            ct0++;
        }
    }

    ll r = n / 2 - k;
    if (ct1 < r || ct0 < r)
    {
        cout << "NO" << endl;
    }
    else
    {
        if ((ct1 - r) % 2 || (ct0 - r) % 2)
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;
        }
    }
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