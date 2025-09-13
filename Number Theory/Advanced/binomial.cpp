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
const ll maxn = 101;

// hui's triangle
vvl tri(maxn, vl(maxn));
void trip(ll n)
{
    for (ll i = 0; i < n; i++)
    {
        tri[i][0] = tri[i][i] = 1;
    }
    for (ll i = 1; i < n; i++)
    {
        for (ll j = 1; j < i; j++)
        {
            tri[i][j] = tri[i - 1][j] + tri[i - 1][j - 1];
        }
    }
}

// combination
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

ll fac[10001], finvs[10001];
void lin_finvs(ll n, ll p)
{
    fac[0] = 1;
    fac[1] = 1;
    for (ll i = 2; i < n + 1; i++)
    {
        fac[i] = (i * fac[i - 1]) % p;
    }

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

    ll ans = (((fac[n] * finvs[m]) % p) * finvs[n - m]) % p;
    return ans;
}

// (i, j) is valid if the C(i, j) % k = 0, find the total number of valid pairs within the ranges i ~ [0, n] and j ~ [0, min(i, m)], all test cases share the same value of k.
vvl c(maxn, vl(maxn, 0));
vvl f(maxn, vl(maxn, 0));
vvl sum(maxn, vl(maxn, 0));
ll k;
void build()
{
    for (ll i = 0; i < maxn; i++)
    {
        c[i][0] = 1; // C(i, 0) = 1
        for (ll j = 1; j < i + 1; j++)
        {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % k;
        }
    }

    // C(i, j) % k == 0
    for (ll i = 1; i < maxn; i++)
    {
        for (ll j = 1; j < i + 1; j++)
        {
            f[i][j] = (c[i][j] == 0) ? 1 : 0;
        }
    }

    // (0,0) to (i,j)
    for (ll i = 1; i < maxn; i++)
    {
        for (ll j = 1; j < i + 1; j++)
        {
            sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + f[i][j];
        }
        if (i + 1 < maxn)
        {
            sum[i][i + 1] = sum[i][i];
        }
    }
}

// derangement problem
// dp[i] = (i - 1) * (dp[i-1] + dp[i-2]);
ll derg(ll n)
{
    ll facn = 1; // n!
    for (ll i = 1; i < n + 1; i++)
    {
        facn *= i;
    }
    ll ans = facn; // i = 0
    ll faci = 1;   // i!
    for (ll i = 1; i < n + 1; i++)
    {
        // i = 1...n
        // (-1)^i * (n! / i!)
        faci = faci * i;
        if ((i & 1) == 0)
        {
            ans += facn / faci;
        }
        else
        {
            ans -= facn / faci;
        }
    }
    return ans;
}