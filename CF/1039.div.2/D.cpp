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
    vl p(n), dp(n + 2, 0);
    for (ll i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    if (n > 0)
    {
        dp[n - 1] = 1;
    }

    // dp[i]: for all subarrays [i..j] (j>=i) that start with i, the sum of their LDS lengths
    // ans = sum{i=0..n-1} dp[i]
    for (ll i = n - 2; i >= 0; --i)
    {
        // dp[i] = dp[i+1] + ((n-1) - (i+1) + 1) + [i, i]
        if (p[i] > p[i + 1])
        {
            dp[i] = dp[i + 1] + (n - i);
        }
        // dp[i] = dp[i+2] + ((n-1) - (i+2) + 1) + [i, i] + [i+1, i+1]
        else
        {
            dp[i] = dp[i + 2] + (n - i);
        }
    }

    ll ans = 0;
    for (ll i = 0; i < n; i++)
        ans += dp[i];
    cout << ans << "\n";
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