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
using vvl = vector<vl>;
const ll maxn = 2e5 + 5;

vl a(maxn), dp(maxn);
deque<ll> q[maxn];
void solve()
{
    ll n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        q[i].clear();
    }
    for (ll i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    // max(dp[i-1], dp[s-1] + v)
    // there exits v times 'v' between s to v
    for (int i = 1; i <= n; i++)
    {
        dp[i] = dp[i - 1], q[a[i]].emplace_back(i);
        if (q[a[i]].size() > a[i])
        {
            q[a[i]].pop_front();
        }
        if (q[a[i]].size() == a[i])
        {
            dp[i] = max(dp[i], dp[q[a[i]].front() - 1] + a[i]);
        }
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