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
const ll maxn = 2e5 + 5;

vl a(maxn);
// mex = m, [0...m-1] √
bool check(ll m, ll n, ll k)
{
    // cout << "m: " << m << endl;
    if (m == 0)
        return true;
    vl vis(m, 0);
    for (ll i = 0, cnt = 0; i < n; i++)
    {
        if (a[i] < m && vis[a[i]] == 0)
        {
            vis[a[i]] = 1;
            cnt++;
            if (cnt == m)
            {
                fill(vis.begin(), vis.end(), 0);
                cnt = 0;
                k--;
                if (k == 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void solve()
{
    ll n, k;
    cin >> n >> k;
    for (ll i = 0; i < n; i++)
        cin >> a[i];

    ll ans = 0;
    ll l = 0, r = n;
    while (l <= r)
    {
        ll m = (l + r) / 2;
        if (check(m, n, k))
        {
            ans = m;
            l = m + 1;
        }
        else
        {
            r = m - 1;
        }
    }
    cout << ans << endl;
}
signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}