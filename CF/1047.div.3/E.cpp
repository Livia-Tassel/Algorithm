#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#define ll int
using namespace std;
using vl = vector<ll>;

vl a(200005);
void transform(ll n)
{
    vl vis(n + 1, 0);
    for (ll i = 0; i < n; i++)
    {
        vis[a[i]]++;
    }
    ll mex;
    for (ll k = 0; k <= n; k++)
    {
        if (!vis[k])
        {
            mex = k;
            break;
        }
    }
    // cout << "mex=" << mex << endl;
    for (ll i = 0; i < n; i++)
    {
        if (vis[a[i]] > 1 || a[i] > mex)
        {
            a[i] = mex;
        }
    }
}

void solve(ll n, ll k)
{
    if (k > 3)
    {
        k = 2 + (k % 2);
    }

    for (ll s = 0; s < k; s++)
    {
        transform(n);
    }

    long long ans = 0;
    for (ll i = 0; i < n; i++)
    {
        // cout << a[i] << " ";
        ans += a[i];
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
        ll n, k;
        cin >> n >> k;
        for (ll i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        solve(n, k);
    }
}