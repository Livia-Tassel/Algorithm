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
using vvl = vector<vector<ll>>;

ll solve(ll n)
{
    if (n < 2)
    {
        return 0;
    }

    vl a(n);
    for (ll i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    // maximum subarray sum of a[0...i]
    vl l(n);

    // Kadane's Algorithm
    ll cml = 0;
    ll gml = LLONG_MIN;

    for (ll i = 0; i < n; ++i)
    {
        cml = max(a[i], cml + a[i]);
        gml = max(gml, cml);
        l[i] = gml;
    }

    // maximum subarray sum of a[i...n-1]
    vl r(n);

    ll cmr = 0;
    ll gmr = LLONG_MIN;

    for (ll i = n - 1; i > -1; --i)
    {
        cmr = max(a[i], cmr + a[i]);
        gmr = max(gmr, cmr);
        r[i] = gmr;
    }

    // l[i] + r[i+1]
    ll res = LLONG_MIN;
    for (ll i = 0; i < n - 1; ++i)
    {
        res = max(res, l[i] + r[i + 1]);
    }
    return res;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;
    cout << solve(n);

    return 0;
}