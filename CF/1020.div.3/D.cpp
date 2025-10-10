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
    ll n, m;
    cin >> n >> m;
    vl a(n);
    vl b(m);
    for (ll i = 0; i < n; ++i)
        cin >> a[i];
    for (ll i = 0; i < m; ++i)
        cin >> b[i];

    vl l_match(m, -1);
    ll p_a = 0, p_b = 0;
    while (p_a < n && p_b < m)
    {
        if (a[p_a] >= b[p_b])
        {
            l_match[p_b++] = p_a;
        }
        p_a++;
    }

    vl r_match(m, -1);
    p_a = n - 1, p_b = m - 1;
    while (p_a >= 0 && p_b >= 0)
    {
        if (a[p_a] >= b[p_b])
        {
            r_match[p_b--] = p_a;
        }
        p_a--;
    }

    if (l_match[m - 1] != -1)
    {
        cout << 0 << "\n";
        return;
    }

    ll k = LLONG_MAX;
    for (ll i = 0; i < m; ++i)
    {
        // l_match[i-1] + i + r_match[i+1]
        ll l = (i > 0) ? l_match[i - 1] : -1;
        ll r = (i < m - 1) ? r_match[i + 1] : n;

        if ((i == 0 || l != -1) &&
            (i == m - 1 || r != -1) &&
            l < r)
        {
            k = min(k, b[i]);
        }
    }

    if (k == LLONG_MAX)
    {
        cout << -1 << "\n";
    }
    else
    {
        cout << k << "\n";
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