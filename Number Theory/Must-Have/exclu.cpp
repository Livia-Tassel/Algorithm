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
const ll maxn = 1e5 + 1;
// X1 ∪ X2 ∪ ... ∪ Xk
// C(k, 1) - C(k, 2) + ... - C(k, k-1) + C(k, k)

// array, return the number of subsequences whose gcd equals 1.
vl cnt(maxn, 0), tp(maxn, 0), dp(maxn);
void build()
{
    tp[0] = 1;
    for (ll i = 1; i < maxn; i++)
    {
        tp[i] = (2 * tp[i - 1]) % mod;
    }
}
ll sub_gcd()
{
    build();
    for (ll i = maxn - 1; i > 0; i--)
    {
        ll ct = 0;
        for (ll j = i; j < maxn; j += i)
        {
            ct += cnt[j];
        }
        dp[i] = (tp[ct] - 1 + mod) % mod;

        for (ll j = 2 * i; j < maxn; j += i)
        {
            dp[i] = (dp[i] - dp[j] + mod) % mod;
        }
    }
    return dp[1];
}

// return the number of subsequences whose gcd equals k: keeping only k and its multiples, the problem is transformed into the base problem of gcd equals 1.

// 4 types of coins with fixed denominations, for each query, give the quantity of each coin type and a target amount, return the methods.
vl dp(maxn, 0), val(4), cnt(4);
void f()
{
    // make a target amount with an unlimited supply of coins.
    dp[0] = 1;
    for (ll i = 0; i < 4; i++)
    {
        for (ll j = val[i]; j < maxn; j++)
        {
            dp[j] += dp[j - val[i]];
        }
    }
}
ll coins(ll tar)
{
    ll ill = 0;
    // 0001 → 1111, using the exceeding state for val[0], val[1], val[2], and val[3] yuan.
    for (ll s = 1; s < 16; s++)
    {
        ll t = tar;
        ll sign = -1;
        for (ll bit = 0; bit < 4; bit++)
        {
            if ((s >> bit) & 1)
            {
                t -= val[bit] * (cnt[bit] + 1);
                sign = -sign;
            }
        }
        if (t >= 0)
        {
            ill += sign * dp[t];
        }
    }
    return dp[tar] - ill;
}

// you have n different songs, and your wife wanna to listen to l songs, songs can be repeated, but each song must be played at least once, a song can only be played again after k songs, return the play methods.
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

ll fac[101], finvs[101]; // i! % p; 1/i! %p
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

// without the first limitation
// A(n, k + 1) * (n - k)^(l - k - 1)
// = A(n, k) * (n - k)^(l - k)
ll playlists(ll n, ll l, ll k)
{
    // i missing songs.
    // (-1)^i * C(n, i) * f(n-i, l, k), i = 0, 1, 2, 3, ..., n-k-1
    // (-1)^i * n! * (n-i-k)^(l-k) / (i! * (n-i-k)!)
    lin_finvs(100, mod);
    ll tmp, ans = 0, sign = 1;
    for (ll i = 0; i < n - k; i++, sign = (sign != 1 ? 1 : (mod - 1)))
    {
        tmp = (sign * qpow(n - i - k, l - k, mod)) % mod;
        tmp = (tmp * fac[n]) % mod;
        tmp = (tmp * finvs[i]) % mod;
        tmp = (tmp * finvs[n - i - k]) % mod;
        ans = (ans + tmp) % mod;
    }

    return ans;
}