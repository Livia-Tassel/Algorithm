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
    vl a(n);
    for (auto &i : a)
        cin >> i;

    vl b(n + 1);
    ll ans = 0;
    // for each i % 2 == 1, a[i] >= a[i-1] + a[i+1]
    // then a[i] -> b[i], 0 <= b[i] <= a[i]
    // min(sum(a[i] - b[i])), i = 0, 2, 4...
    // max(sum(b[i])), i = 0, 2, 4...
    for (ll i = 0; i < n; i += 2)
    {
        ll mn = a[i];
        // b[i] <= a[i]
        // i >= 2, b[i] <= a[i-1] - b[i-2]
        // i + 1 < n, b[i] <= a[i+1] - b[i+2], b[i+2] >= 0, then b[i] <= a[i+1]
        // b[i] <= min(a[i], a[i-1] - b[i-2], a[i+1])
        // dp[i] = dp[i-1] + min(a[i], a[i-1] - b[i-2], a[i+1])
        if (i >= 2)
        {
            mn = min(mn, a[i - 1] - b[i - 2]);
        }
        if (i + 1 < n)
        {
            mn = min(mn, a[i + 1]);
        }
        b[i] = mn;
        ans += (a[i] - b[i]);
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