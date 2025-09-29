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
void f(vl &diff, ll l, ll r)
{
    diff[l]++, diff[r + 1]--;
}
ll pres(vl &pre, ll m)
{
    if (m == 0)
        return 0;
    else
        return pre[m - 1] - m;
}

void solve(ll n)
{
    vl diff(n + 2, 0), cnt(n + 2, 0), pre(n + 2, 0), suff(n + 2, 0), vis(n + 1, 0);
    // convert iterating over k to iterating over the contribution of all mex to k, thereby transforming it into a difference array.
    for (ll i = 1; i <= n; i++)
    {
        cin >> a[i];
        cnt[a[i]]++;
    }
    pre[0] = cnt[0], suff[n] = cnt[n], vis[0] = (cnt[0] ? 1 : 0);
    for (ll i = 1; i <= n; i++)
    {
        pre[i] = pre[i - 1] + cnt[i];
        vis[i] = vis[i - 1] & (cnt[i] ? 1 : 0);
    }
    for (ll i = n - 1; i >= 0; i--)
    {
        suff[i] = suff[i + 1] + cnt[i];
    }

    for (ll m = 0, l, r; m <= n; m++)
    {
        if (!vis[m])
        {
            l = 0;
            r = suff[m + 1] + pres(pre,m);
            f(diff, l, r);
            break;
        }

        l = cnt[m];
        r = cnt[m] + suff[m + 1] + pres(pre,m);
        f(diff, l, r);
    }

    cout << diff[0] << " ";
    for (ll i = 1; i <= n; i++)
    {
        diff[i] += diff[i - 1];
        cout << diff[i] << " ";
    }
    cout << endl;
}
signed main()
{
    ll t, n, k;
    cin >> t;
    while (t--)
    {
        cin >> n;
        solve(n);
    }
}