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
ll bs;

ll fcf(string s, ll n)
{
    ll tol = 0;
    for (ll i = 0; i < n; ++i)
    {
        if (s[i] == '0')
        {
            // l (0...i)
            // r (i...n-1)
            tol += (i + 1) * (n - i);
        }
    }
    return tol;
}

void update(vl &bit, ll i, ll delta)
{
    for (; i < bs; i += i & -i)
    {
        bit[i] += delta;
    }
}
ll query(vl &bit, ll i)
{
    ll sum = 0;
    for (; i > 0; i -= i & -i)
    {
        sum += bit[i];
    }
    return sum;
}
ll fmx(string s, ll n)
{
    ll off = n;
    bs = 2 * n + 2;
    vl bcnt(bs, 0);
    vl bsum(bs, 0);

    ll tol = 0, pre = 0;
    // s[i] == '1' => a[i] = 1
    // s[i] == '0' => a[i] = -1
    // p = s[l...r], ap = a[l...r]
    // ct(p) - cf(p) => sum(ap)
    // Σsum(ap), sum(ap) > 0,
    // for the specific 'r', l = 0 to r, pref[r+1] > pref[l], then Σ(pref[r+1] - pref[l])

    ll vf = pre + off;
    update(bcnt, vf + 1, 1);
    update(bsum, vf + 1, pre);

    for (ll i = 0; i < n; ++i)
    {
        ll val = (s[i] == '1' ? 1 : -1);
        pre += val;
        vf = pre + off;

        ll cs = query(bcnt, vf);
        ll ss = query(bsum, vf);

        tol += cs * pre - ss;

        update(bcnt, vf + 1, 1);
        update(bsum, vf + 1, pre);
    }
    return tol;
}

void solve()
{
    ll n;
    cin >> n;
    string s;
    cin >> s;
    // max(a, b) = a + max(0, b - a)
    // max(a, b) = b + max(0, a - b)
    // f(p) = max(cf(p), ct(p))
    // Σf(p) = Σ(cf(p) + max(0, ct(p) - cf(p)))
    // = Σcf(p) + Σmax(0, ct(p) - cf(p))

    ll ans = 0;
    ans = fcf(s, n) + fmx(s, n);
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