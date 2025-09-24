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
ll solve(ll n, ll k)
{
    ll ans = 0, cnt = 0;
    for (ll i = 0; i < n; i++)
        cin >> a[i];

    for (ll i = 0; i < n; i++)
    {
        cnt = a[i] != 0 ? 0 : cnt + 1;

        if (cnt >= k)
        {
            // cout << "cnt: " << cnt << endl;
            // cout << "i: " << i << endl;
            ans++, i++;
            cnt = 0;
        }
    }
    return ans;
}
signed main()
{
    ll t, n, k;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        cout << solve(n, k) << endl;
    }
}