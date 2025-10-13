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

bool check(ll m, ll k, ll len)
{
    return m - k >= m / (len + 1);
}
void solve()
{
    ll n, m;
    cin >> n >> m;
    ll k;
    cin >> k;
    k = (k + n - 1) / n;
    ll l = 1, r = m, ans = m;
    while (l <= r)
    {
        ll mid = (l + r) / 2;
        if (check(m, k, mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
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