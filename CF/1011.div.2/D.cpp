#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <queue>
#include <numeric>
#include <cstdio>
#include <unordered_map>
#define ll long long
using namespace std;
using vl = vector<ll>;

void solve()
{
    ll n, k;
    cin >> n >> k;
    // dp[i][r] = (dp[i-1][r], dp[i-1][r-k] + di, dp[i-1][r+1])

    vl d(n + 1);
    ll ans = 0;
    priority_queue<ll> q;
    for (ll i = 1; i <= n; i++)
    {
        cin >> d[i];
        q.push(d[i]);
        // since each selection costs k+1 minutes, a maximum of n / (k+1) selections can be made. Therefore, we inevitably choose the maximum number of selections. A greedy choice is made to pick the plate with the current highest score only when the number of remaining minutes, n - i + 1, is exactly a multiple of k+1.
        if ((n - i + 1) % (k + 1) == 0)
        {
            ans += q.top();
            q.pop();
        }
    }
    cout << ans << endl;
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