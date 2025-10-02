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

string L, R;
ll memo[11][2][2];

ll f(ll i, bool tl, bool tr)
{
    if (i == L.length())
    {
        return 0;
    }
    if (memo[i][tl][tr] != -1)
    {
        return memo[i][tl][tr];
    }

    ll ans = 1e9;
    ll ld = tl ? (L[i] - '0') : 0;
    ll ud = tr ? (R[i] - '0') : 9;

    for (ll dg = ld; dg <= ud; ++dg)
    {
        ll cur = 0;
        if (dg == (L[i] - '0'))
        {
            cur++;
        }
        if (dg == (R[i] - '0'))
        {
            cur++;
        }
        ans = min(ans, cur + f(i + 1, tl && (dg == ld), tr && (dg == ud)));
    }

    return memo[i][tl][tr] = ans;
}

void solve()
{
    ll l, r;
    cin >> l >> r;
    L = to_string(l);
    R = to_string(r);

    for (ll i = 0; i < 11; i++)
    {
        for (ll j = 0; j < 2; j++)
        {
            for (ll k = 0; k < 2; k++)
            {
                memo[i][j][k] = -1;
            }
        }
    }
    cout << f(0, true, true) << endl;
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
    return 0;
}