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
using vvd = vector<vector<double>>;
using vd = vector<double>;
using vl = vector<ll>;
const ll maxn = 11;

ll d, x, y, px, py;
void exgcd(ll a, ll b)
{
    if (b == 0)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}
ll mul(ll a, ll b, ll mod)
{
    a = (a % mod + mod) % mod;
    b = (b % mod + mod) % mod;
    ll ans = 0;
    while (b != 0)
    {
        if ((b & 1) != 0)
        {
            ans = (ans + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}
vl m(maxn, 0), r(maxn, 0);
ll crt(ll n)
{
    ll lcm = 1;
    for (ll i = 1; i < n + 1; i++)
    {
        lcm = lcm * m[i];
    }
    ll ai, ci, ans = 0;
    for (ll i = 1; i < n + 1; i++)
    {
        // ai = lcm / m[i]
        ai = lcm / m[i];
        // ai^(-1)
        exgcd(ai, m[i]);
        // ci = (ri * ai * ai^(-1)) % lcm
        ci = mul(r[i], mul(ai, x, lcm), lcm);
        ans = (ans + ci) % lcm;
    }
    return ans;
}

ll excrt(ll n)
{
    ll tail = 0, lcm = 1, tmp, b, c, x0;
    // ans = lcm * x + tail
    for (ll i = 1; i < n + 1; i++)
    {
        // ans = m[i] * y + ri
        // lcm * x + m[i] * y = ri - tail
        // a = lcm
        // b = m[i]
        // c = ri - tail
        b = m[i];
        c = ((r[i] - tail) % b + b) % b;
        exgcd(lcm, b);
        if (c % d != 0)
        {
            return -1;
        }
        // x0 = (x * (c/d)) % (b/d)
        // x = x0 + (b/d) * n
        x0 = mul(x, c / d, b / d);
        // ans = lcm * x + tail
        // ans = lcm * (x0 + (b/d) * n) + tail
        // ans = lcm * (b/d) * n + lcm * x0 + tail
        // tail' = tail' % lcm'
        tmp = lcm * (b / d);
        tail = (tail + mul(x0, lcm, tmp)) % tmp;
        lcm = tmp;
    }
    return tail;
}

// n dragons, each with initial hp and a rc ability, set of swords with different at powers; dragons are fought sequentially, for each at, a sword is chosen according to specific rules; after killing a dragon, the sword used is consumed and a new rd sword is gained; the hero's strategy is to at each dragon exactly ans times, then wait for its hp to recover to exactly 0 to kill it, find the minimum ans required to kill all dragons under this strategy.
ll hp[maxn], rc[maxn], rd[maxn], init[maxn], at[maxn];
map<ll, ll> sorted;
ll allocate(ll n, ll m)
{
    sorted.clear();
    for (ll i = 1; i < m + 1; i++)
    {
        sorted[init[i]]++;
    }

    ll max_hits = 0;
    for (ll i = 1; i < n + 1; i++)
    {
        auto it = sorted.upper_bound(hp[i]);
        ll ai;
        if (it == sorted.begin())
        {
            ai = sorted.begin()->first;
        }
        else
        {
            ai = (--it)->first;
        }

        at[i] = ai;
        sorted[ai]--;
        if (sorted[ai] == 0)
        {
            sorted.erase(ai);
        }
        sorted[rd[i]]++;

        max_hits = max(max_hits, (hp[i] + at[i] - 1) / at[i]);
        hp[i] %= rc[i];
    }
    return max_hits;
}

ll compute(ll n, ll m)
{
    ll max_val = allocate(n, m);
    ll tail = 0, lcm = 1, tmp, a, b, c, x0;

    for (ll i = 1; i <= n; i++)
    {
        // at[i] * ans ≡ hp[i] (mod rc[i])
        // ans = k * lcm + tail
        // -> at[i] * (k*lcm + tail) ≡ hp[i] (mod rc[i])
        // -> (at[i]*lcm) * k ≡ hp[i] - at[i]*tail (mod rc[i])
        a = mul(at[i], lcm, rc[i]);
        b = rc[i];
        c = ((hp[i] - mul(at[i], tail, b)) % b + b) % b;

        exgcd(a, b);
        if (c % d != 0)
        {
            return -1;
        }

        ll b_d = b / d;
        x0 = mul(x, c / d, b_d);

        tmp = lcm * b_d;
        tail = (tail + mul(x0, lcm, tmp)) % tmp;
        lcm = tmp;
    }

    ll ans;
    if (tail >= max_val)
    {
        ans = tail;
    }
    else
    {
        // ans = k * lcm + tail >= max_val
        // k >= (max_val - tail) / lcm
        // k_min = ceil((max_val - tail) / lcm)
        ll k = (max_val - tail + lcm - 1) / lcm;
        ans = k * lcm + tail;
    }
    return ans;
}