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
    ll ans = 1;
    ll n;
    cin >> n;
    vl a(n);
    for (ll i = 0; i < n; i++)
        cin >> a[i];
    ll lt = a[0];
    for (ll i = 1; i < n; i++)
    {
        if (lt + 1 < a[i])
        {
            lt = a[i];
            ans++;
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