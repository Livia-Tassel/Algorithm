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
vl a;

bool check(ll v, ll &out_l, ll &out_r)
{
    // b_i: +1 if a_i >= v else -1
    vl ps(n + 1, 0);
    for (ll i = 1; i <= n; ++i)
    {
        ll b = (a[i] >= v) ? 1 : -1;
        ps[i] = ps[i - 1] + b;
    }

    // min prefix ps[j] for j in [0..i-k]
    ll min_pos = 0;
    ll min_val = ps[0];
    for (ll i = k; i <= n; ++i)
    {
        if (ps[i - k] < min_val)
        {
            min_val = ps[i - k];
            min_pos = i - k;
        }
        // max(sum[j, i]), j in [0, i-k+1]
        // => ps[i] - min(sum[0, max(0, j-1)]), j in [0, i-k+1]
        // => ps[i] - min_val
        if (ps[i] - min_val >= 0)
        {
            out_l = min_pos + 1;
            out_r = i;
            return true;
        }
    }
    return false;
}

void solve()
{
    cin >> n >> k;
    a.assign(n + 1, 0);
    for (ll i = 1; i <= n; ++i)
        cin >> a[i];

    ll L = 1, R = n;
    ll best_v = 1, best_l = 1, best_r = k;
    while (L <= R)
    {
        ll mid = (L + R) >> 1;
        ll l, r;
        if (check(mid, l, r))
        {
            best_v = mid;
            best_l = l;
            best_r = r;
            L = mid + 1;
        }
        else
        {
            R = mid - 1;
        }
    }
    cout << best_v << " " << best_l << " " << best_r << "\n";
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