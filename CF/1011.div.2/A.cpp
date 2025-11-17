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
    bool ok = false;
    for (ll i = 1; i < s.length(); i++)
    {
        if (s[i] != s[0])
        {
            ok = true;
            break;
        }
    }
    if (!ok)
    {
        cout << "NO" << endl;
        return;
    }

    if (k != 0)
    {
        cout << "YES" << endl;
    }
    else
    {
        for (ll l = 0, r = n - 1; l <= r; l++, r--)
        {
            if (s[l] < s[r])
            {
                cout << "YES" << endl;
                return;
            }
            if (s[l] > s[r])
            {
                cout << "NO" << endl;
                return;
            }
        }
        cout << "NO" << endl;
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}