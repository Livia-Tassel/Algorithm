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

ll start[maxn], split[maxn], se;
void build(ll n)
{
    se = 0;
    for (ll s = 1, p = 2; p < n + 1; s *= 3, p = s * 3 - 1)
    {
        start[++se] = s;
        split[se] = p;
    }
}
void reverse(vl &arr, ll l, ll r)
{
    while (l < r)
    {
        swap(arr[l++], arr[r--]);
    }
}
void rotate(vl &arr, ll l, ll m, ll r)
{
    reverse(arr, l, m);
    reverse(arr, m + 1, r);
    reverse(arr, l, r);
}
ll to(ll i, ll l, ll r)
{
    ll n = r - l + 1;
    ll mid = (l + r) / 2;
    if (i - 1 < mid)
    {
        return l + 2 * (i - l);
    }
    else
    {
        return l + 2 * (i - (mid + 1)) + 1;
    }
}

void circle(vl &arr, ll l, ll r, ll i)
{
    for (ll j = 1, init, cur, next, curv, nextv; j < i + 1; j++)
    {
        init = cur = l + start[j] - 1;
        next = to(cur, l, r);
        curv = arr[cur];
        while (next != init)
        {
            nextv = arr[next];
            arr[next] = curv;
            curv = nextv;
            cur = next;
            next = to(cur, l, r);
        }
        arr[init] = curv;
    }
}
// O(n), O(1)
void shuffle(vl &arr, ll l, ll r)
{
    ll n = r - l + 1;
    build(n);
    for (ll i = se; n > 0;)
    {
        if (split[i] < n + 1)
        {
            ll m = (l + r) / 2;
            rotate(arr, l + split[i] / 2, m, m + split[i] / 2);
            circle(arr, l, l + split[i] - 1, i);
            l += split[i];
            n -= split[i];
        }
        else
        {
            i--;
        }
    }
}

// sort arr, make sure that: arr[0] < arr[1] > arr[2] < arr[3] > ...
ll first, last;
ll sele(vl &arr, ll n, ll i)
{
    ll ans = 0;
    for (ll l = 0, r = n - 1; l < r + 1;)
    {
        pt(arr, l, r, arr[l + (ll)(rand() * (r - l + 1))]);
        if (i < first)
        {
            r = first - 1;
        }
        else if (i > last)
        {
            l = last + 1;
        }
        else
        {
            ans = arr[i];
            break;
        }
    }
    return ans;
}
void pt(vl &arr, ll l, ll r, ll x)
{
    first = l;
    last = r;
    ll i = l;
    while (i < last + 1)
    {
        if (arr[i] == x)
        {
            i++;
        }
        else if (arr[i] < x)
        {
            swap(arr[first++], arr[i++]);
        }
        else
        {
            swap(arr[i], arr[last--]);
        }
    }
}
void gsort(vl &arr, ll n)
{
    sele(arr, n, n / 2);
    if ((n & 1) == 0)
    {
        shuffle(arr, 0, n - 1);
        reverse(arr, 0, n - 1);
    }
    else
    {
        shuffle(arr, 1, n - 1);
    }
}