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
const ll maxn = 10001;

// ll arr[maxn], fac[maxn], tree[maxn];
// ll n;
// ll lowbit(ll i)
// {
//     return i & -i;
// }
// ll sum(ll i)
// {
//     ll ans = 0;
//     while (i > 0)
//     {
//         ans = (ans + tree[i]) % mod;
//         i -= lowbit(i);
//     }
//     return ans;
// }
// void add(ll i, ll v)
// {
//     while (i <= n)
//     {
//         tree[i] += v;
//         i += lowbit(i);
//     }
// }
// determining the lexicographical rank of a given permutation.
// ll compute()
// {
//     fac[0] = 1;
//     for (ll i = 1; i < n; i++)
//     {
//         fac[i] = (fac[i - 1] * i) % mod;
//     }

//     for (ll i = 1; i <= n; i++)
//     {
//         tree[i] = 0;
//     }
//     for (ll i = 1; i <= n; i++)
//     {
//         add(i, 1);
//     }

//     ll ans = 0;
//     for (ll i = 1; i <= n; i++)
//     {
//         ans = (ans + (sum(arr[i] - 1) * fac[n - i]) % mod) % mod;
//         add(arr[i], -1);
//     }

//     ans = (ans + 1) % mod; // 1-base
//     return ans;
// }

// array s of length n that represents a specific permutation of numbers from 1 to n, find the rank x of this permutation, and then print the permutation at rank x+m.
ll arr[maxn], sum[maxn << 2];
ll n, m;

void build(ll l, ll r, ll i)
{
    if (l == r)
    {
        sum[i] = 1;
    }
    else
    {
        ll mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

void add(ll jobi, ll jobv, ll l, ll r, ll i)
{
    if (l == r)
    {
        sum[i] += jobv;
    }
    else
    {
        ll mid = (l + r) >> 1;
        if (jobi <= mid)
        {
            add(jobi, jobv, l, mid, i << 1);
        }
        else
        {
            add(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
}

ll qsum(ll jobl, ll jobr, ll l, ll r, ll i)
{
    if (jobl <= l && r <= jobr)
    {
        return sum[i];
    }
    ll mid = (l + r) >> 1;
    ll ans = 0;
    if (jobl <= mid)
    {
        ans += qsum(jobl, jobr, l, mid, i << 1);
    }
    if (jobr > mid)
    {
        ans += qsum(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

ll gd(ll k, ll l, ll r, ll i)
{
    ll ans;
    if (l == r)
    {
        sum[i]--;
        ans = l;
    }
    else
    {
        ll mid = (l + r) >> 1;
        if (sum[i << 1] >= k)
        {
            ans = gd(k, l, mid, i << 1);
        }
        else
        {
            ans = gd(k - sum[i << 1], mid + 1, r, i << 1 | 1);
        }
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
    return ans;
}

void compute()
{
    build(1, n, 1);
    for (ll i = 1; i < n + 1; i++)
    {
        ll x = arr[i];
        if (x > 1)
        {
            arr[i] = qsum(1, x - 1, 1, n, 1);
        }
        else
        {
            arr[i] = 0;
        }
        add(x, -1, 1, n, 1);
    }

    arr[n] += m;
    for (ll i = n; i > 1; i--)
    {
        arr[i - 1] += arr[i] / (n - i + 1);
        arr[i] %= (n - i + 1);
    }

    build(1, n, 1);
    for (ll i = 1; i < n + 1; i++)
    {

        arr[i] = gd(arr[i] + 1, 1, n, 1);
    }
}