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
#include <queue>
#define ll long long
using namespace std;
using vl = vector<ll>;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
vl gfac(ll n)
{
    vl fac;
    for (ll i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            fac.push_back(i);
            while (n % i == 0)
            {
                n /= i;
            }
        }
    }
    if (n > 1)
    {
        fac.push_back(n);
    }
    return fac;
}

// min(N -> 1)
ll bfs(ll s, ll k)
{
    if (s == 1)
    {
        return 0;
    }

    map<ll, ll> dist;
    queue<ll> q;

    q.push(s);
    dist[s] = 0;
    while (!q.empty())
    {
        ll curr = q.front();
        q.pop();

        for (ll i = 1; i * i <= curr; ++i)
        {
            if (curr % i == 0)
            {
                // (i, curr/i)
                if (i > 1 && i <= k)
                {
                    ll nd = curr / i;
                    if (dist.find(nd) == dist.end())
                    {
                        dist[nd] = dist[curr] + 1;
                        if (nd == 1)
                            return dist[nd];
                        q.push(nd);
                    }
                }

                if ((curr / i) != i && (curr / i) > 1 && (curr / i) <= k)
                {
                    ll nd = i; // curr / (curr / i)
                    if (dist.find(nd) == dist.end())
                    {
                        dist[nd] = dist[curr] + 1;
                        if (nd == 1)
                            return dist[nd];
                        q.push(nd);
                    }
                }
            }
        }
    }
    return -1;
}

void solve()
{
    ll a, b;
    cin >> a >> b;
    ll k;
    cin >> k;
    if (a == b)
    {
        cout << 0 << endl;
        return;
    }

    ll g = gcd(a, b);
    ll aa = a / g;
    ll bb = b / g;

    vl fac_a = gfac(aa);
    for (ll f : fac_a)
    {
        if (f > k)
        {
            cout << -1 << endl;
            return;
        }
    }

    vl fac_b = gfac(bb);
    for (ll f : fac_b)
    {
        if (f > k)
        {
            cout << -1 << endl;
            return;
        }
    }

    // a -> gcd(a, b), then gcd(a, b) -> b
    // a -> gcd(a, b) <-> a/gcd(a, b) -> 1
    // gcd(a, b) -> b <-> b/gcd(a, b) -> 1
    cout << bfs(aa, k) + bfs(bb, k) << endl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}