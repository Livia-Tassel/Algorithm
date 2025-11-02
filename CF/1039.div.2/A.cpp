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
    ll n, c;
    cin >> n >> c;
    vl a(n);

    ll ans = 0;
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] > c)
        {
            ans++;
        }
    }

    sort(a.begin(), a.end());
    auto it = upper_bound(a.begin(), a.end(), c);
    ll dex = it - a.begin() - 1;
    while (dex >= 0)
    {
        for (ll i = 0; i < dex; i++)
        {
            a[i] *= 2;
        }
        dex--;
        while (dex >= 0 && a[dex] > c)
        {
            dex--;
            ans++;
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