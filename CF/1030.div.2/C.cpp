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
using ll = long long;
using ull = unsigned long long;
using namespace std;
using vl = vector<ll>;

ll lb(ll a)
{
    a = ~(ull)a;
    // if (a == 0)
    // {
    //     return 64;
    // }
    return a & (-a);
}

struct cmp
{
    bool operator()(ll a, ll b) const
    {
        return lb(a) > lb(b);
    }
};

void solve()
{
    ll n, k, ans = 0;
    cin >> n >> k;
    vl a(n);

    priority_queue<ll, vl, cmp> pq;
    for (ll i = 0, t; i < n; i++)
    {
        cin >> a[i];
        t = a[i];
        while (t > 0)
        {
            if ((t & 1) == 1)
            {
                ans++;
            }
            t >>= 1;
        }
        pq.push(a[i]);
    }
    // cout << "ans: " << ans << endl;

    while (k > 0)
    {
        ll x = pq.top();
        pq.pop();
        // cout << x << " " << lb(x) << endl;
        if (k >= lb(x))
        {
            k -= lb(x);
            x += lb(x);
            ans++;
            pq.push(x);
        }
        else
        {
            break;
        }
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