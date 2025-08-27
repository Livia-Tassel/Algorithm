#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;
const ll mod = 1e9 + 7;

// ((a+b) + (c+d)) % mod = ((a+b) % mod + (c+d) % mod) % mod
// ((a*b) * (c*d)) % mod = ((a*b) % mod * (c*d) % mod) % mod
// (a-b) % mod = (a % mod - b % mod + mod) % mod

ll mul(ll a, ll b, ll mod)
{
    ll ans = 0;
    a %= mod;
    while (b > 0)
    {
        if (b & 1)
        {
            ans = (ans + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

ll qpow(ll x, ll n, ll mod)
{
    ll ans = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ans = mul(ans, x, mod);
        }
        x = mul(x, x, mod);
        n >>= 1;
    }
    return ans;
}

ll inv(ll x, ll mod)
{
    return qpow(x, mod - 2, mod);
}

ll div(ll a, ll b, ll mod)
{
    return ((a % mod) * inv(b, mod)) % mod;
}

ll invs[10001];
void lin_inv(ll n, ll p)
{
    invs[1] = 1;
    for (ll i = 2; i < n; i++)
    {
        invs[i] = (p - (invs[p % i] * (p / i)) % p) % p;
    }
}

ll fac[10001], finvs[10001];
void lin_finvs(ll n, ll p)
{
    fac[0] = 1;
    fac[1] = 1;
    for (ll i = 2; i < n + 1; i++)
    {
        fac[i] = (i * fac[i - 1]) % p;
    }

    // for (ll i = 1; i < n; i++)
    // {
    //     finvs[i] = inv(fac[i], p) % p;
    // }
    finvs[n] = inv(fac[n], p);
    for (ll i = n - 1; i >= 0; i--)
    {
        finvs[i] = (finvs[i + 1] * (i + 1)) % p;
    }
}

ll comb(ll n, ll m, ll p)
{
    if (m < 0 || m > n)
        return 0;

    lin_finvs(n, p);

    ll ans = fac[n];
    ans = (ans * finvs[m]) % p;
    ans = (ans * finvs[n - m]) % p;
    return ans;
}

signed main()
{
    cout << comb(537, 367, mod) << endl;
    return 0;
}