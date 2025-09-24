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
#include <queue>
#include <unordered_map>
#define ll long long
using namespace std;
using vl = vector<ll>;
const ll maxn = 2e5 + 5;

struct cont
{
    ll l, r;
    ll earn;
    cont(ll l, ll r, ll en) : l(l), r(r), earn(en) {};
};
struct comp
{
    bool operator()(const cont &a, const cont &b) const
    {
        return a.earn > b.earn;
    }
};

ll solve(ll n, ll k)
{
    ll s = 0;
    vector<cont> cts;
    for (ll i = 0, l, r, real; i < n; i++)
    {
        cin >> l >> r >> real;
        if (r >= k)
        {
            s++;
            cts.push_back(cont(l, r, real));
        }
    }
    sort(cts.begin(), cts.end(), [](const cont &a, const cont &b)
         { return a.l < b.l; });
    if (cts.empty())
        return k;
    priority_queue<cont, vector<cont>, comp> pq;

    ll cnt = 0;
    while (cnt < s && cts[cnt].l <= k)
        pq.push(cts[cnt++]);

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        if (cur.r < k)
            continue;

        k = max(k, cur.earn);
        while (cnt < s && cts[cnt].l <= k)
            pq.push(cts[cnt++]);
    }
    return k;
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