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
const ll maxn = 1e5 + 5;

vl p(maxn), s(maxn);
ll solve(ll n)
{
    bool ok = true;
    cin >> p[0];
    for (ll i = 1; i < n; i++)
    {
        cin >> p[i];
        if (p[i - 1] % p[i] != 0)
            ok = false;
    }
    cin >> s[0];
    for (ll i = 1; i < n; i++)
    {
        cin >> s[i];
        if (s[i] % s[i - 1] != 0)
            ok = false;
    }
    if (!ok)
        return false;

    ll dex;
    for (ll i = 0; i < n; i++)
    {
        if (p[i] == s[i])
        {
            dex = i;
            ok = false;
            break;
        }
    }
    if (ok)
        return false;

    for (ll i = dex + 1; i < n; i++)
        if (p[i] != p[i - 1])
            return false;

    for (ll i = dex - 1; i >= 0; i--)
        if (s[i] != s[i + 1])
            return false;

    return true;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << (solve(n) ? "YES" : "NO") << endl;
    }
}