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
using vs = vector<string>;
using vvs = vector<vs>;
using vb = vector<bool>;
const ll maxn = 2e5 + 5;

void solve()
{
    int n, m;
    cin >> n >> m;
    vs a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    vvs b(m, vs(n));
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
            cin >> b[i][j];
    }

    vb vis(n, false);
    int best = 0;
    for (int i = 0; i < m; ++i)
    {
        int cnt = 0;
        for (int j = 0; j < n; ++j)
        {
            if (b[i][j] == a[j])
            {
                ++cnt;
                vis[j] = true;
            }
        }
        best = max(best, cnt);
    }

    if (!all_of(vis.begin(), vis.end(), [](bool x)
                { return x; }))
    {
        cout << -1 << '\n';
    }
    else
    {
        cout << (n + 2 * (n - best)) << '\n';
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
