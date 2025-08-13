#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#define ll long long
using namespace std;
const ll MAXN = 1001;
vector<ll> arr(MAXN), pre(MAXN);

// longest subarray whose sum equals a target value.
ll lon_sub(ll goal, ll n)
{
    ll ans = 0;
    map<ll, ll> mp;
    mp[0] = 0;
    for (ll i = 1; i <= n; i++)
    {
        pre[i] = arr[i] + pre[i - 1];
        if (!mp.count(pre[i]))
        {
            mp[pre[i]] = i;
        }
        cout << "pre[" << i << "]:" << pre[i] << endl;
    }

    for (ll i = 1; i <= n; i++)
    {
        if (mp.count(pre[i] - goal))
        {
            ans = max(ans, i - mp[pre[i] - goal]);
        }
    }

    pre.clear();
    return ans;
}

// number of subarrays whose sum equals a target value.
ll num_sub(ll goal, ll n) // goal != 0
{
    ll ans = 0;
    map<ll, ll> mp;
    mp[0] = 1;

    for (ll i = 1, sum = 0; i <= n; i++)
    {
        sum += arr[i];
        ans += mp[sum - goal];
        mp[sum]++;
    }

    pre.clear();
    return ans;
}

// longest subarray with an equal number of positive and negative numbers.
ll equ_sub(ll n)
{
    ll ans = 0;
    for (ll i = 1, sum = 0; i <= n; i++)
    {
        arr[i] > 0 ? sum += 1 : sum -= 1;
        if (!sum)
        {
            ans = max(ans, i);
        }
    }

    pre.clear();
    return ans;
}

// longest subarray with a sum greater than 0.
ll gre_sub(ll n)
{
    ll ans = 0;
    map<ll, ll> mp;
    mp[0] = 0;

    for (ll i = 1, sum = 0; i <= n; i++)
    {
        arr[i] > 0 ? sum += 1 : sum -= 1;

        if (sum > 0)
        {
            ans = i;
        }
        else
        {
            // -1 -1 -1 -1 -1  1  1 -1  1
            // -1 -2 -3 -4 -5 -4 -3 -4 -3
            if (mp.count(sum - 1))
            {
                ans = max(ans, i - mp[sum - 1]);
            }

            if (!mp.count(sum))
            {
                mp[sum] = i;
            }
        }
    }

    pre.clear();
    return ans;
}

// remove the shortest subarray so that the sum of the remaining elements can be divided by p.
ll div_sub(ll n, ll p)
{
    ll ans = LLONG_MAX;
    map<ll, ll> mp; // key means prefix sums modulo p, and value means the latest position of that remainder.
    mp[0] = 0;

    ll mod = 0;
    for (ll i = 1; i <= n; i++)
    {
        mod = (mod + arr[i]) % p;
    }
    cout << "mod=" << mod << endl;
    if (mod == 0)
    {
        return 0;
    }

    for (ll i = 1, cur = 0, find; i <= n; i++)
    {
        cur = (cur + arr[i]) % p;
        find = cur >= mod ? (cur - mod) : (cur + p - mod);

        if (mp.count(find))
        {
            ans = min(ans, i - mp[find]);
        }

        mp[cur] = i;
    }

    pre.clear();
    arr.clear();
    return ans;
}

// longest substring where the count of each vowel is even.
ll move(char ch)
{
    switch (ch)
    {
    case 'a':
        return 0;
    case 'e':
        return 1;
    case 'i':
        return 2;
    case 'o':
        return 3;
    case 'u':
        return 4;
    default:
        return -1;
    }
}

ll even_sub(string s)
{
    ll n = s.length(), ans = 0;
    // u o i e a   status
    // 0 0 0 0 0
    vector<ll> mp(32, -2); // all states have not appeared yet.
    mp[0] = -1;

    for (ll i = 0, status = 0, m; i < n; i++)
    {
        m = move(s[i]);
        if (m != -1)
        {
            status ^= (1LL << m);
        }

        if (mp[status] != -2)
        {
            ans = max(ans, i - mp[status]);
        }
        else
        {
            mp[status] = i;
        }
    }
    return ans;
}

