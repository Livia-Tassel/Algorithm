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
#define endl '\n'
using namespace std;
using vl = vector<ll>;
const ll maxn = 200005;

vl a(maxn), b(maxn), s(2 * maxn), pra(maxn), prb(maxn), pran(2 * maxn), prbn(2 * maxn);
ll n, m, q, pa, pb, ps;
void build()
{
    sort(a.begin() + 1, a.begin() + n + 1, greater<ll>());
    sort(b.begin() + 1, b.begin() + m + 1, greater<ll>());

    ps = 1, pa = 1, pb = 1;
    pran[0] = 0, prbn[0] = 0;
    while (pa <= n && pb <= m)
    {
        if (a[pa] >= b[pb])
        {
            s[ps] = a[pa++];
            pran[ps] = pran[ps - 1] + 1;
            prbn[ps] = prbn[ps - 1];
        }
        else
        {
            s[ps] = b[pb++];
            prbn[ps] = prbn[ps - 1] + 1;
            pran[ps] = pran[ps - 1];
        }
        ps++;
    }
    if (pa <= n)
    {
        while (pa <= n)
        {
            s[ps] = a[pa++];
            pran[ps] = pran[ps - 1] + 1;
            prbn[ps] = prbn[ps - 1];
            ps++;
        }
    }
    else
    {
        while (pb <= m)
        {
            s[ps] = b[pb++];
            prbn[ps] = prbn[ps - 1] + 1;
            pran[ps] = pran[ps - 1];
            ps++;
        }
    }

    pra[0] = 0, prb[0] = 0;
    for (ll i = 1; i <= n; i++)
    {
        pra[i] = pra[i - 1] + a[i];
    }
    for (ll i = 1; i <= m; i++)
    {
        prb[i] = prb[i - 1] + b[i];
    }
}
ll solve()
{
    ll x, y, k;
    cin >> x >> y >> k;
    if (k <= 0)
        return 0;

    ll an = pran[k], bn = prbn[k]; // an + bn == k
    if (an <= x && bn <= y)
    {
        return pra[an] + prb[bn];
    }
    else if (an >= x)
    {
        return pra[x] + prb[k - x];
    }
    else
    {
        return pra[k - y] + prb[y];
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m >> q;
        for (ll i = 1; i <= n; i++)
            cin >> a[i];
        for (ll i = 1; i <= m; i++)
            cin >> b[i];

        build();
        while (q--)
        {
            cout << solve() << endl;
        }
    }
    return 0;
}