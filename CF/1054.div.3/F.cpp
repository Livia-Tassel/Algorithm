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

// rest r times
bool check(ll h, ll d, ll r)
{
    ll segn = r + 1;
    ll q = d / segn;
    ll rem = d % segn;

    // rem segments remove q+1 times
    ll ans = rem * (q + 1) * (q + 2) / 2;

    // (segn-rem) segments remove q times
    ans += (segn - rem) * q * (q + 1) / 2;

    return h + r > ans;
}

void solve()
{
    ll h, d;
    cin >> h >> d;
    ll l = 0, r = d, rest = d;

    while (l <= r)
    {
        ll m = l + (r - l) / 2;
        if (check(h, d, m))
        {
            rest = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }

    cout << d + rest << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}