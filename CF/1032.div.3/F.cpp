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
// count subsegments with sum equals s
ll seg(vl &arr, ll s)
{
    if (arr.empty())
    {
        return 0;
    }
    map<ll, ll> pcnt;
    pcnt[0] = 1;

    ll sum = 0, cnt = 0;
    for (ll val : arr)
    {
        sum += val;
        if (pcnt.count(sum - s))
        {
            cnt += pcnt[sum - s];
        }
        pcnt[sum]++;
    }
    return cnt;
}

ll f(vl &arr, ll s, ll x)
{
    // (seg with sum euqals s) - (seg with sum euqals s and without x)
    ll cnt_all = seg(arr, s);

    ll cnt_nox = 0;
    vl mb;
    for (ll val : arr)
    {
        if (val == x)
        {
            if (!mb.empty())
            {
                cnt_nox += seg(mb, s);
            }
            mb.clear();
        }
        else
        {
            mb.push_back(val);
        }
    }
    if (!mb.empty())
    {
        cnt_nox += seg(mb, s);
    }
    return cnt_all - cnt_nox;
}

void solve()
{
    ll n, s, x;
    cin >> n >> s >> x;
    for (ll i = 0; i < n; ++i)
        cin >> a[i];

    ll ans = 0;
    vl cb;

    for (ll i = 0; i < n; ++i)
    {
        if (a[i] > x)
        {
            if (!cb.empty())
            {
                ans += f(cb, s, x);
                cb.clear();
            }
        }
        else
        {
            cb.push_back(a[i]);
        }
    }

    // the last block
    if (!cb.empty())
    {
        ans += f(cb, s, x);
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