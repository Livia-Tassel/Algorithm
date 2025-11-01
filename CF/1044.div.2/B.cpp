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
    ll n, ans = 0;
    cin >> n;
    vl g(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> g[i];
    }
    sort(g.begin(), g.end());
    if (n % 2 == 1)
    {
        for (ll i = 0; i < n; i += 2)
        {
            ans += g[i];
        }
    }
    else
    {
        for (ll i = 1; i < n; i += 2)
        {
            ans += g[i];
        }
    }
    cout << ans << endl;
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