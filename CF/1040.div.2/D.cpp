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
    vl p(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    // x_i = 0, p_i; x_i = 1, 2*n - p_i
    // C = Inv(P) + sum_{1, n}(x_i * (sum_{j > i}[p_i < p_j] - sum_{j < i}[p_j > p_i]))
    // for each i, x_i * (R_i - L_i), L_i = sum_{j < i}[p_j > p_i], R_i = sum_{j > i}[p_i < p_j]
    // R_i - L_i >= 0, then x_i = 0
    // R_i - L_i < 0, then x_i = 1
    for (ll i = 0; i < n; i++)
    {
        ll l = 0, r = 0;
        for (ll j = 0; j < i; j++)
        {
            if (p[j] > p[i])
            {
                l++;
            }
        }
        for (ll j = i + 1; j < n; j++)
        {
            if (p[j] > p[i])
            {
                r++;
            }
        }
        ans += min(l, r);
    }
    cout << ans << '\n';
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