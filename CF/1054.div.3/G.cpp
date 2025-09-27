#pragma GCC optimize(2)
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
#include <random>
#include <chrono>
#define ll long long
#define pb push_back
#define all(v) v.begin(), v.end()
#define endl '\n'
using namespace std;
using vl = vector<ll>;
const ll maxn = 2e5 + 5;

// a[l, r], cnt(a[i]) > ⌊len/3⌋+ 1
// cnt(i) <= 2, i satisfies the above condition.
vl g[maxn];
mt19937 rd(chrono::high_resolution_clock::now().time_since_epoch().count());
void solve()
{
    ll n, q;
    cin >> n >> q;

    vl a(n + 1);
    vl div;
    for (ll i = 0; i <= n; i++)
    {
        g[i].clear();
    }

    for (ll i = 1; i <= n; i++)
    {
        cin >> a[i];
        div.pb(a[i]);
    }

    sort(all(div));
    div.erase(unique(all(div)), div.end());

    for (ll i = 1; i <= n; i++)
    {
        // compressed position
        ll cp = lower_bound(all(div), a[i]) - div.begin() + 1;
        g[cp].pb(i);
    }

    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        ll k = 40;
        const ll th = (r - l + 1) / 3;
        uniform_int_distribution<ll> grp(l, r); // [l, r]
        set<ll> res;

        while (k--)
        {
            ll radx = grp(rd);
            ll val = a[radx];
            ll cp = lower_bound(all(div), val) - div.begin() + 1;
            auto &pos = g[cp];
            // count times of val of range [l, r]
            ll cnt = upper_bound(all(pos), r) - lower_bound(all(pos), l);

            if (cnt > th)
            {
                res.insert(val);
            }
            if (res.size() >= 2)
            {
                break;
            }
        }

        if (res.empty())
        {
            cout << -1 << endl;
        }
        else
        {
            bool flag = true;
            for (auto const &val : res)
            {
                if (!flag)
                {
                    cout << " ";
                }
                cout << val;
                flag = false;
            }
            cout << endl;
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
