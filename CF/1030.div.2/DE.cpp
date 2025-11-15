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

ll n, k;
vl p, d;

// memo[i][t][dir]
//  0: NO, 1: YES
ll memo[505][505][2];
bool vis[505][505][2];

ll dfs(ll i, ll t, ll dir)
{
    if (memo[i][t][dir] != -1)
    {
        return memo[i][t][dir];
    }

    // reach the same location with the same state, thus forming a loop.
    if (vis[i][t][dir])
    {
        return memo[i][t][dir] = 0;
    }

    vis[i][t][dir] = true;
    bool is_red = (t == d[i]);
    int final_dir = dir;
    if (is_red)
    {
        final_dir = 1 - dir; // turn around
    }

    ll res;
    if (final_dir == 0)
    { // right
        if (i == n - 1)
        {
            res = 1;
        }
        else
        {
            ll next_i = i + 1;
            ll delta_t = p[next_i] - p[i];
            ll next_t = (t + delta_t) % k;
            res = dfs(next_i, next_t, 0);
        }
    }
    else
    { // left
        if (i == 0)
        {
            res = 1;
        }
        else
        {
            ll next_i = i - 1;
            ll delta_t = p[i] - p[next_i];
            ll next_t = (t + delta_t) % k;
            res = dfs(next_i, next_t, 1);
        }
    }
    vis[i][t][dir] = false;
    return memo[i][t][dir] = res;
}

void solve()
{
    cin >> n >> k;
    p.resize(n);
    d.resize(n);
    for (ll i = 0; i < n; ++i)
        cin >> p[i];
    for (ll i = 0; i < n; ++i)
        cin >> d[i];

    for (ll i = 0; i < n; ++i)
    {
        for (ll j = 0; j < k; ++j)
        {
            memo[i][j][0] = memo[i][j][1] = -1;
            vis[i][j][0] = vis[i][j][1] = false;
        }
    }

    ll q;
    cin >> q;
    for (ll j = 0; j < q; ++j)
    {
        ll a;
        cin >> a;
        auto it = lower_bound(p.begin(), p.end(), a);
        ll i = it - p.begin();

        if (it == p.end())
        {
            cout << "YES\n";
            continue;
        }

        ll start_i;
        ll start_t;
        ll start_dir = 0;

        if (p[i] == a)
        {
            start_i = i;
            start_t = 0;
        }
        else
        {
            start_i = i;
            start_t = (p[i] - a) % k;
        }

        if (dfs(start_i, start_t, start_dir) == 1)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
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