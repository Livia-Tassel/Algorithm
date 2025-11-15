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
    vl p(n), d(n);
    for (ll i = 0; i < n; i++)
        cin >> p[i];
    for (ll i = 0; i < n; i++)
        cin >> d[i];

    map<ll, vl> mpl, mpr;
    map<ll, ll> traffic;
    for (ll i = 0; i < n; i++)
    {
        traffic[p[i]] = d[i];
        mpl[(d[i] + p[i]) % k].emplace_back(p[i]);
        mpr[(((d[i] - p[i]) % k) + k) % k].emplace_back(p[i]);
    }

    auto nl = [&](ll pos, ll t)
    {
        // (t + p)(mod k) remains unchanged when moving left on all green lights.
        ll val = (t + pos) % k;
        auto &vec = mpl[val];
        auto it = lower_bound(vec.begin(), vec.end(), pos);
        if (it == vec.begin())
            return -1ll;
        it--;
        return *it;
    };

    auto nr = [&](ll pos, ll t)
    {
        // (t - p)(mod k) remains unchanged when all green lights move to the right.
        ll val = (((t - pos) % k) + k) % k;
        auto &vec = mpr[val];
        auto it = lower_bound(vec.begin(), vec.end(), pos + 1);
        if (it == vec.end())
            return -1ll;
        return *it;
    };

    map<pair<ll, ll>, bool> dp;
    ll q;
    cin >> q;

    for (ll i = 0; i < q; i++)
    {
        ll x;
        cin >> x;
        ll dir = 1, t = 0;

        set<pair<ll, ll>> states;

        bool ok = false;
        if (traffic.count(x) && traffic[x] == 0)
            dir ^= 1;

        for (ll it = 0; it < 2 * n; it++)
        {
            ll y = dir ? nr(x, t) : nl(x, t);
            if (y == -1)
            {
                ok = true;
                break;
            }
            else
            {
                t += abs(y - x);
                x = y;
                dir ^= 1;
            }

            if (states.count({x, dir}))
                break;
            states.insert({x, dir});

            if (dp.count({x, dir}))
            {
                ok = dp[{x, dir}];
                break;
            }
        }

        for (auto [a, b] : states)
        {
            dp[{a, b}] = ok;
        }

        cout << (ok ? "YES\n" : "NO\n");
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