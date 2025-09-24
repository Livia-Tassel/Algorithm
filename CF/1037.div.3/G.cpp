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
const ll maxn = 2e5 + 100;

vl a(maxn), b(maxn), preb(maxn), premin(maxn), suffmax(maxn);
ll solve(ll n)
{
    for (ll i = 1; i <= n; i++)
        cin >> a[i];

    ll ans = 0;
    for (ll i = 1; i <= 100; i++)
    {
        // med >= i <=> preb[l,r] > 0
        for (ll j = 1; j <= n; j++)
        {
            if (a[j] >= i)
                b[j] = 1;
            else
                b[j] = -1;
        }

        for (ll j = 1; j <= n; j++)
        {
            preb[j] = preb[j - 1] + b[j];
        }

        premin[0] = 0, suffmax[n] = preb[n];
        for (ll j = 1; j <= n; j++)
        {
            premin[j] = min(premin[j - 1], preb[j]);
        }
        for (ll j = n - 1; j >= 1; j--)
        {
            suffmax[j] = max(suffmax[j + 1], preb[j]);
        }

        for (ll j = 1; j <= n; j++)
        {
            // preb(l,j] > 0 || preb[j,r) > 0
            // med - min >= i - a[j]
            if (premin[j - 1] <= preb[j] || preb[j - 1] <= suffmax[j])
            {
                ans = max(ans, i - a[j]);
            }
        }
    }
    return ans;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << solve(n) << endl;
    }
}