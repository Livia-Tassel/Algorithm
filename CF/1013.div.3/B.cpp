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
    ll n, l;
    cin >> n >> l;
    vl a(n);
    for (ll i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end(), greater<ll>());
    // for (ll i = 0; i < n; i++)
    //     cout << a[i] << " ";
    // cout << endl;
    ll ans = 0, sum = 0;
    for (ll i = 0, last = -1; i < n; i++)
    {
        if (a[i] >= l)
        {
            ans++;
            last = i;
        }
        else
        {
            if ((i - last) * a[i] >= l)
            {
                ans++;
                last = i;
            }
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