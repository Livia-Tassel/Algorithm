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
using vpll = vector<pair<ll, ll>>;
using vi = vector<int>;

ll gs(vl &arr)
{
    return arr.size();
}
void solve()
{
    ll n;
    cin >> n;
    vpll pts(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> pts[i].first >> pts[i].second;
    }

    if (n <= 2)
    {
        cout << n << '\n';
        return;
    }

    vl as_all, bs_all;
    as_all.reserve(n);
    bs_all.reserve(n);
    unordered_map<ll, int> cta, ctb;
    cta.reserve(n * 2);
    ctb.reserve(n * 2);

    for (ll i = 0; i < n; i++)
    {
        ll x = pts[i].first;
        ll y = pts[i].second;
        as_all.push_back(x);
        bs_all.push_back(y);
        cta[x]++;
        ctb[y]++;
    }

    vl as = as_all;
    vl bs = bs_all;
    sort(as.begin(), as.end());
    as.erase(unique(as.begin(), as.end()), as.end());
    sort(bs.begin(), bs.end());
    bs.erase(unique(bs.begin(), bs.end()), bs.end());

    ll l = as.front();
    ll r = as.back();
    ll u = bs.front();
    ll d = bs.back();

    ll baseArea = (r - l + 1) * (d - u + 1);
    ll ans = baseArea;

    vi cand;
    cand.reserve(n);
    vi used(n, 0);
    for (int i = 0; i < (int)n; i++)
    {
        if (!used[i] && (pts[i].first == l || pts[i].first == r || pts[i].second == u || pts[i].second == d))
        {
            used[i] = 1;
            cand.push_back(i);
        }
    }

    for (int idx : cand)
    {
        ll ai = pts[idx].first;
        ll bi = pts[idx].second;

        ll nl = l, nr = r, nu = u, nd = d;

        if (cta[ai] == 1)
        {
            if (ai == l)
                nl = (gs(as) >= 2 ? as[1] : ai);
            if (ai == r)
                nr = (gs(as) >= 2 ? as[gs(as) - 2] : ai);
        }
        if (ctb[bi] == 1)
        {
            if (bi == u)
                nu = (gs(bs) >= 2 ? bs[1] : bi);
            if (bi == d)
                nd = (gs(bs) >= 2 ? bs[gs(bs) - 2] : bi);
        }

        ll w = nr - nl + 1;
        ll h = nd - nu + 1;
        ll area = w * h;

        ll candAns;
        if (area > n - 1)
            candAns = area;
        else
            candAns = area + min(w, h);

        ans = min(ans, candAns);
    }

    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
