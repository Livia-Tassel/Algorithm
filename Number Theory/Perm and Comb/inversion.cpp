#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;
using ll = long long;
using vl = vector<ll>;
const ll MAXN = 500005;
ll bit[MAXN];
ll n;

void add(ll i, ll val)
{
    for (; i < n + 1; i += i & -i)
    {
        bit[i] += val;
    }
}

ll query(ll i)
{
    ll sum = 0;
    for (; i > 0; i -= (i & -i))
    {
        sum += bit[i];
    }
    return sum;
}

ll inv(const vector<ll> &p)
{
    for (ll i = 1; i < n + 1; ++i)
    {
        bit[i] = 0;
    }
    ll invs = 0;
    for (ll i = 0; i < n; ++i)
    {
        invs += query(n) - query(p[i]);
        add(p[i], 1);
    }
    return invs;
}

void solve()
{
    cin >> n;
    vl a(n), b(n);
    // (ai.bi + aj.bj) < (ajbi + aibj)
    // (ai - aj)(bi - bj) < 0
    // ai < aj, bi > bj
    for (ll i = 0; i < n; ++i)
        cin >> a[i];
    for (ll i = 0; i < n; ++i)
        cin >> b[i];

    ll inv_a = inv(a), inv_b = inv(b);
    string res = "";

    // the parity of the number of 'discordant pairs' between two permutations is the same as the parity of the sum of the number of inversions respectively.
    ll pa = inv_a % 2, pb = inv_b % 2;
    res += (pa + pb) % 2 != 0 ? 'A' : 'B';

    for (ll k = 0; k < n - 1; ++k)
    {
        char t;
        ll l, r, d;
        cin >> t >> l >> r >> d;

        ll len = r - l + 1;
        if ((d % 2 != 0) && ((len - 1) % 2 != 0))
        {
            t != 'A' ? pb = 1 - pb : pa = 1 - pa;
        }
        res += (pa + pb) % 2 != 0 ? 'A' : 'B';
    }
    cout << res << "\n";
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