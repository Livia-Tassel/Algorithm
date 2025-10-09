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
    ll n;
    cin >> n;
    map<ll, vl> col;
    map<ll, vl> row;

    for (ll i = 0, a, b; i < n; i++)
    {
        cin >> a >> b;
        row[a].push_back(b);
        col[b].push_back(a);
    }

    if (n <= 2)
    {
        cout << n << endl;
        return;
    }

    auto get_bounds = [&](map<ll, vl> &m) -> pair<ll, ll>
    {
        if (m.empty())
            return {0, 0};
        return {m.begin()->first, m.rbegin()->first};
    };

    auto [l, r] = get_bounds(col);
    auto [u, d] = get_bounds(row);

    ll ans = (r - l + 1) * (d - u + 1);

    auto try_remove = [&](map<ll, vl> &col, map<ll, vl> &row, bool is_col, ll key)
    {
        if ((is_col && col[key].size() < 2) || (!is_col && row[key].size() < 2))
        {
            ll other = (is_col ? col[key][0] : row[key][0]);
            if (is_col)
            {
                col.erase(key);
                if (row.count(other))
                    row.erase(other);
            }
            else
            {
                row.erase(key);
                if (col.count(other))
                    col.erase(other);
            }

            if (!col.empty() && !row.empty())
            {
                ll l = col.begin()->first;
                ll r = col.rbegin()->first;
                ll u = row.begin()->first;
                ll d = row.rbegin()->first;
                ll area = (r - l + 1) * (d - u + 1);
                if (area > n - 1)
                    return min(ans, area);
                else
                    return min(ans, area + min(r - l + 1, d - u + 1));
            }
        }
        return ans;
    };

    ans = try_remove(col, row, true, l);
    ans = try_remove(col, row, true, r);
    ans = try_remove(col, row, false, u);
    ans = try_remove(col, row, false, d);

    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}