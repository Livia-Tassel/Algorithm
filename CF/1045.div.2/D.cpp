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
#include <functional>
#define ll long long
using namespace std;
using vl = vector<ll>;
using vvl = vector<vl>;

void solve()
{
    ll n;
    cin >> n;
    vvl g(n);
    for (ll i = 0; i < n - 1; i++)
    {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vl dist(n), p(n);
    function<void(ll, ll)> dfs = [&](ll now, ll par)
    {
        p[now] = par;
        for (ll i : g[now])
        {
            if (i != par)
            {
                dist[i] = dist[now] + 1;
                dfs(i, now);
            }
        }
    };

    dist[0] = 0;
    dfs(0, -1);
    ll x = max_element(dist.begin(), dist.end()) - dist.begin();

    dist[x] = 0;
    dfs(x, -1);
    ll y = max_element(dist.begin(), dist.end()) - dist.begin();

    if (dist[y] == n - 1)
    {
        cout << -1 << '\n';
        return;
    }

    vl on_diameter(n);
    ll now = y;
    while (now != -1)
    {
        on_diameter[now] = 1;
        now = p[now];
    }

    ll a = -1, b = -1, c = -1;
    for (ll u = 0; u < n; u++)
    {
        for (ll v : g[u])
        {
            // the first branch point
            if (on_diameter[u] && !on_diameter[v])
            {
                a = p[u], b = u, c = v;
                break;
            }
        }
        if (a != -1)
            break;
    }
    cout << a + 1 << ' ' << b + 1 << ' ' << c + 1 << '\n';
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