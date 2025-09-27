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
// <= k, <= len
ll most(ll k, ll n, ll len)
{
    if (len == 0)
        return 0;

    ll ans = 0;
    map<ll, ll> freq;
    ll l = 0;
    for (ll r = 0, cnt = 0; r < n; ++r)
    {
        if (++freq[a[r]] == 1)
        {
            cnt++;
        }

        while (cnt > k)
        {
            freq[a[l]]--;
            if (freq[a[l]] == 0)
            {
                freq.erase(a[l]);
                cnt--;
            }
            l++;
        }

        // subarr end with r
        ans += min(r - l + 1, len);
    }
    return ans;
}
ll solve(ll n)
{
    ll k, l, r;
    cin >> k >> l >> r;
    for (ll i = 0; i < n; i++)
        cin >> a[i];
    return (most(k, n, r) - most(k - 1, n, r)) - (most(k, n, l - 1) - most(k - 1, n, l - 1));
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << solve(n) << endl;
    }
}