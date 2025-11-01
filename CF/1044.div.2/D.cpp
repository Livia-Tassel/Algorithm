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
    vl h(n + 1), dp(n + 1, 0);
    for (ll i = 1; i <= n; i++)
    {
        cin >> h[i];
    }

    // mob never takes fall damage more than once
    // (1) kill the first i-1 mob using dp[i-1] and get one fall damage
    // (2) directly kill the (i-1)-th mob and get i-1 fall damage
    // (3) directly kill the i-th mob and then using dp[i-1], clearly less optimal than the first case
    dp[1] = h[1];
    for (ll i = 2; i <= n; i++)
    {
        dp[i] = min(dp[i - 1] + h[i] - 1, dp[i - 2] + h[i - 1] + max(0LL, h[i] - (i - 1)));
    }
    cout << dp[n] << endl;
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