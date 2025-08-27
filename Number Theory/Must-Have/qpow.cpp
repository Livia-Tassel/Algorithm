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

// safe qpow
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

vvl mmul(vvl &a, vvl &b)
{
    ll n = a.size(), m = b[0].size();
    ll p = a[0].size();
    vvl res(n, vl(m, 0));
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            for (ll k = 0; k < p; k++)
            {
                res[i][j] = (a[i][k] * b[k][j] + res[i][j]) % mod;
            }
        }
    }
    return res;
}

// logp * n^3
vvl mpow(vvl &a, ll p)
{
    ll n = a.size();
    vvl res(n, vl(n, 0));
    for (ll i = 0; i < n; i++)
    {
        res[i][i] = 1;
    }

    for (; p != 0; p >>= 1)
    {
        if ((p & 1) != 0)
        {
            res = mmul(res, a);
        }
        a = mmul(a, a);
    }
    return res;
}

// logn * k^3
// matrix qpow solve "1d k-th order", for example, the fibonacci sequence, f(n) = f(n-1) + f(n-2).
ll fibo(ll n)
{
    if (n < 2)
        return n;
    vvl r = {{1, 1}, {1, 0}};
    vvl rn = mpow(r, n - 1);
    vvl f = {{1, 0}};
    vvl fn = mmul(f, rn);
    return fn[0][0];
}
// f(n) = af(n-1) + bf(n-2) + cf(n-3) + ...
//       [a x x]
// r  →  [b x x]
//       [c x x]

// two types of tiles, how many ways to tile a 2 x n board.
// . . x   . o x   x x o
// o o x   . o x   x o o
ll f(ll n, ll r)
{
    if (n == 0)
        return r != 0 ? 0 : 1;
    if (n == 1)
        return 1;

    // n > 1
    if (r == 1)
        return f(n - 1, 1) + f(n - 1, 0);
    else
        return f(n - 1, 0) + f(n - 2, 0) + 2 * f(n - 2, 1);
}
// f(n) = 2f(n-1) + f(n-3)
ll tilings(ll n)
{
    if (n < 2)
        return n;
    vvl r = {{2, 1, 0}, {0, 0, 1}, {1, 0, 0}};
    vvl rn = mpow(r, n - 1);
    vvl f = {{5, 2, 1}};
    vvl fn = mmul(f, rn);
    return fn[0][0];
}

// logn * k^3
// matrix qpow solve "kd 1-th order", for example, dp[i][3] = dp[i-1][2] + dp[i-1][3] - dp[i-1][4].

// count the number of strings of length n that can be formed according to the following rules:
// only a e i o u
// u → a → e → a/i
// i !→ i, o → i/u

// dp[i][j] valid strings of length i that end with character j.
// dp[i][a] = dp[i-1][e/i/u]
// dp[i][e] = dp[i-1][a/i]
// dp[i][i] = dp[i-1][e/o]
// dp[i][o] = dp[i-1][i]
// dp[i][u] = dp[i-1][i/o]
ll vowel(ll n)
{
    if (n < 2)
        return 5;
    vvl r = {{0, 1, 0, 0, 0},
             {1, 0, 1, 0, 0},
             {1, 1, 0, 1, 1},
             {0, 0, 1, 0, 1},
             {1, 0, 0, 0, 0}};
    vvl rn = mpow(r, n - 1);
    vvl f = {{1, 1, 1, 1, 1}};
    vvl fn = mmul(f, rn);

    ll ans = 0;
    for (ll x : fn[0])
    {
        ans = (x + ans) % mod;
    }
    return ans;
}

// string length n, A: absent, L: late, P: present, consider it valid if the total count of 'A's is less than 2, and there is no consecutive sequence of 'L's of length 3 or more, how many valid strings.

// dp[i][a][l] the first i days, exists a absences and exactly l consecutive days of being late at the end.
// dp[i][0][0] → dp[i][0]
// dp[i][0][1] → dp[i][1]
// dp[i][0][2] → dp[i][2]
// dp[i][1][0] → dp[i][3]
// dp[i][1][1] → dp[i][4]
// dp[i][1][2] → dp[i][5]
// dp[i][a][l] → dp[i][3a+l]

// dp[i][0] = dp[i-1][0/1/2]
// dp[i][1] = dp[i-1][0]
// dp[i][2] = dp[i-1][1]
// dp[i][3] = dp[i-1][0/1/2/3/4/5]
// dp[i][4] = dp[i-1][3]
// dp[i][5] = dp[i-1][4]
ll record(ll n)
{
    if (n < 2)
        return 3;
    vvl r = {{1, 1, 0, 1, 0, 0},
             {1, 0, 1, 1, 0, 0},
             {1, 0, 0, 1, 0, 0},
             {0, 0, 0, 1, 1, 0},
             {0, 0, 0, 1, 0, 1},
             {0, 0, 0, 1, 0, 0}};
    vvl rn = mpow(r, n - 1);
    vvl f = {{1, 1, 0, 1, 0, 0}};
    vvl fn = mmul(f, rn);

    ll ans = 0;
    for (ll x : fn[0])
    {
        ans = (x + ans) % mod;
    }
    return ans;
}