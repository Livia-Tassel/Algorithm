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
const ll mod = 1e9 + 7;
const ll maxn = 1001;

vl fac(maxn), finv(maxn), inv(maxn);
ll qpow(ll x, ll p)
{
    ll ans = 1;
    x %= mod;
    while (p > 0)
    {
        if ((p & 1) == 1)
        {
            ans = (ans * x) % mod;
        }
        x = (x * x) % mod;
        p >>= 1;
    }
    return ans;
}

void build(ll n)
{
    fac[0] = 1;
    fac[1] = 1;
    for (ll i = 2; i < n + 1; i++)
    {
        fac[i] = (i * fac[i - 1]) % mod;
    }

    finv[0] = 1;
    finv[n] = qpow(fac[n], mod - 2);
    for (ll i = n - 1; i > 0; i--) // i!^(-1) % p
    {
        finv[i] = ((i + 1) * finv[i + 1]) % mod;
    }

    inv[1] = 1;
    for (ll i = 2; i < n + 2; i++) // i^(-1) % p
    {
        inv[i] = (mod - (inv[mod % i] * (mod / i)) % mod) % mod;
    }
}

ll c(ll n, ll k)
{
    if (k < 0 || k > n)
        return 0;
    return (((fac[n] * finv[k]) % mod) * finv[n - k]) % mod;
}

// C(n) = C(2n, n) - C(2n, n-1)
ll f1(ll n)
{
    if (n == 0)
        return 1;
    build(2 * n);
    return (c(2 * n, n) - c(2 * n, n - 1) + mod) % mod;
}

// C(n) = C(2n, n) / (n+1)
ll f2(ll n)
{
    if (n == 0)
        return 1;
    build(2 * n);
    return (c(2 * n, n) * qpow(n + 1, mod - 2)) % mod;
}

// C(n) = (4n-2)/(n+1) * C(n-1)
ll f3(ll n)
{
    build(n);
    vl f(n + 1);
    f[0] = 1;
    if (n >= 1)
        f[1] = 1;
    for (ll i = 2; i < n + 1; i++)
    {
        f[i] = f[i - 1] * (4 * i - 2) % mod * inv[i + 1] % mod;
    }
    return f[n];
}

// C(n) = sum_{i=0..n-1} C(i) * C(n-1-i)
ll f4(ll n)
{
    vl f(n + 1);
    f[0] = 1;
    for (ll i = 1; i < n + 1; i++)
    {
        for (ll l = 0, r = i - 1; l < i; l++, r--)
        {
            f[i] = (f[i] + f[l] * f[r]) % mod;
        }
    }
    return f[n];
}

// factor counting method
// O(n)
vl minpf(maxn), prime(maxn), ct(maxn);
ll cnt;
void euler(ll n)
{
    fill(minpf.begin(), minpf.begin() + n + 1, 0);
    cnt = 0;
    for (ll i = 2; i < n + 1; i++)
    {
        if (minpf[i] == 0)
        {
            prime[cnt++] = i;
        }
        for (ll j = 0; j < cnt; j++)
        {
            if (i * prime[j] > n)
            {
                break;
            }
            minpf[i * prime[j]] = prime[j];
            if (i * prime[j] == 0)
            {
                break;
            }
        }
    }
}

ll compute(ll n, ll mod)
{
    euler(2 * n);

    fill(ct.begin(), ct.begin() + 2 * n + 2, 0);
    for (ll i = 2; i < n + 1; ++i)
        ct[i] = -1;

    for (ll i = n + 2; i < 2 * n + 1; ++i)
        ct[i] = 1;

    for (ll i = 2 * n; i > 1; i--)
    {
        if (minpf[i] != 0)
        {
            ct[minpf[i]] += ct[i];
            ct[i / minpf[i]] += ct[i];
            ct[i] = 0;
        }
    }

    ll ans = 1;
    for (ll i = 2; i < 2 * n + 1; i++)
    {
        if (ct[i] != 0)
        {
            ans = ans * qpow(i, ct[i]) % mod;
        }
    }
    return ans;
}
