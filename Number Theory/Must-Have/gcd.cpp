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
const ll mod = 1e9 + 7;

ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}

ll f(ll x, ll a, ll b)
{
    return x / a + x / b - x / lcm(a, b);
}

// the n-th number divisible by a or b.
ll n_magic_num(ll n, ll a, ll b)
{
    ll ans = 0;
    ll l = 0, r = min(a, b) * n, m;
    while (l <= r)
    {
        m = (l + r) / 2;
        if (f(m, a, b) >= n)
        {
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    return ans % mod;
}

signed main()
{
    cout << n_magic_num(100, 2, 3) << endl;
    return 0;
}

// gcd(a^b, c^d)
constexpr ll mod = 998244353;
constexpr ll inf = 1e9 + 5;
constexpr ll qpow(ll a, ll b)
{
    ll ans = 1;
    a %= mod;
    while (b > 0)
    {
        if (b % 2)
        {
            ans = (a * ans) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans % mod;
}
ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}
void solve()
{
    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    ll ans = 1;
    while (true)
    {
        if (b == d)
        {
            ans *= qpow(gcd(a, c), b);
            ans %= mod;
            break;
        }

        ll g = gcd(a, c);

        if (g == 1)
        {
            break;
        }

        if (b > d)
        {
            ans *= qpow(g, d);
            ans %= mod;
            c /= g;
            b -= d;
        }
        else
        {   // d > b
            ans *= qpow(g, b);
            ans %= mod;
            a /= g;
            d -= b;
        }
    }

    cout << ans << '\n';
}