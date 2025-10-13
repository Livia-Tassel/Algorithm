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
using vs = vector<string>;
const ll maxn = 1e7 + 5;
const ll mod = 1e9 + 7;

void solve()
{
    ll n, m, d;
    cin >> n >> m >> d;
    vs a(n);
    for (ll i = 0; i < n; ++i)
        cin >> a[i];

    ll W = d;
    ll H = 0;
    if (d >= 1)
    {
        long double tmp = (long double)d * (long double)d - 1.0L;
        if (tmp < 0)
            H = 0;
        else
            H = (ll)floor(sqrt(tmp) + 1e-12L);
    }

    vl prevWays(m + 2, 0);
    vl has(m + 2, 0);

    fill(has.begin(), has.end(), 0);
    for (ll col = 1; col <= m; ++col)
        if (a[n - 1][col - 1] == 'X')
            has[col] = 1;

    vl cntPref(m + 2, 0);
    for (ll col = 1; col <= m; ++col)
        cntPref[col] = cntPref[col - 1] + has[col];

    for (ll col = 1; col <= m; ++col)
    {
        if (!has[col])
        {
            prevWays[col] = 0;
            continue;
        }
        ll L = max(1LL, col - W);
        ll R = min(m, col + W);
        ll ngb = cntPref[R] - cntPref[L - 1];
        ngb -= 1;
        ll val = 1 + ngb;
        prevWays[col] = (val % mod + mod) % mod;
    }

    for (ll row = n - 2; row >= 0; --row)
    {
        vl hasCur(m + 2, 0);
        for (ll col = 1; col <= m; ++col)
            if (a[row][col - 1] == 'X')
                hasCur[col] = 1;

        vl prevPref(m + 2, 0);
        for (ll col = 1; col <= m; ++col)
        {
            prevPref[col] = (prevPref[col - 1] + prevWays[col]) % mod;
        }

        vl startSum(m + 2, 0);
        for (ll col = 1; col <= m; ++col)
        {
            if (!hasCur[col])
                continue;
            ll L = max(1LL, col - H);
            ll R = min(m, col + H);
            ll s = (prevPref[R] - prevPref[L - 1]) % mod;
            if (s < 0)
                s += mod;
            startSum[col] = s;
        }

        vl startPref(m + 2, 0);
        for (ll col = 1; col <= m; ++col)
        {
            startPref[col] = (startPref[col - 1] + startSum[col]) % mod;
        }

        vl newWays(m + 2, 0);
        for (ll col = 1; col <= m; ++col)
        {
            if (!hasCur[col])
                continue;
            ll waysSingle = startSum[col];
            ll L = max(1LL, col - W);
            ll R = min(m, col + W);
            ll waysPair = (startPref[R] - startPref[L - 1]) % mod;
            if (waysPair < 0)
                waysPair += mod;
            waysPair = (waysPair - startSum[col]) % mod;
            if (waysPair < 0)
                waysPair += mod;

            ll total = (waysSingle + waysPair) % mod;
            newWays[col] = total;
        }

        prevWays.swap(newWays);
    }

    ll ans = 0;
    for (ll col = 1; col <= m; ++col)
    {
        if (a[0][col - 1] == 'X')
        {
            ans += prevWays[col];
            if (ans >= mod)
                ans -= mod;
        }
    }
    cout << ans % mod << '\n';
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