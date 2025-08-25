#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <climits>
#include <set>
#define ll long long
using namespace std;

// arr[i] is the maximum jump distance from index i, starting from index 0, find the minimum number of jumps required to reach the last index n-1.
ll jump(vector<ll> &arr)
{
    ll n = arr.size();
    ll cur = 0, next = 0, ans = 0;
    for (ll i = 0; i < n; i++)
    {
        if (cur < i)
        {
            ans++;
            cur = next;
        }
        // next records the maximum potential reach of the positions reachable in the previous ans jumps.
        next = max(next, i + arr[i]);
    }
    return ans;
}

// garden length n and n+1 sprinklers at positions [0, 1, ..., n], each sprinkler i has a watering range of [i - ranges[i], i + ranges[i]], find the minimum number of sprinklers required to water the entire garden.
ll taps(ll n, vector<ll> &rg)
{
    ll r[10001] = {0};
    for (ll i = 0, l; i < n + 1; i++)
    {
        l = (i - rg[i]) > 0 ? (i - rg[i]) : 0;
        r[l] = max(rg[l], i + rg[i]);
    }

    ll cur = 0, next = 0, ans = 0;
    for (ll i = 0; i < n + 1; i++)
    {
        if (cur < i)
        {
            if (next < i)
            {
                return -1;
            }
            ans++;
            cur = next;
        }
        next = max(next, r[i]);
    }
    return ans;
}

// n people cross a river, each with a specific crossing time, the boat can hold at most two people, total time for two people to cross the river equals max(t_i, t_j), find the minimum total time for everyone to cross.
ll cross(vector<ll> &t)
{
    // 1 2 3
    // 2 → 1 3
    // 1 2 ← 3
    // → 1 2 3
    sort(t.begin(), t.end());
    ll dp[100001];
    ll n = t.size();
    if (n < 2)
    {
        return t[0];
    }
    else if (n < 3)
    {
        return t[1];
    }
    else if (n < 4)
    {
        return t[0] + t[1] + t[2];
    }
    else
    {
        dp[0] = t[0], dp[1] = t[1], dp[2] = t[0] + t[1] + t[2];
        for (ll i = 3; i < n; i++)
        {
            dp[i] = min(t[i] + t[0] + dp[i - 1], t[i] + 2 * t[1] + t[0] + dp[i - 2]);
        }
    }
    return dp[n - 1];
}

// some clothes in n machines, you can simultaneously move one piece of clothing from several machines to an adjacent machine, find the minimum number of steps to make the number of clothes in all machines equal.
ll moves(vector<ll> &mh)
{
    // 0 3 0
    // 1 2 0
    // 1 1 1 √
    ll sum = 0, n = mh.size();
    for (ll clo : mh)
    {
        sum += clo;
    }
    if (sum % n != 0)
    {
        return -1;
    }

    ll ln, rn, avg = sum / n, ans = 0;
    sum = 0;
    for (ll i = 0; i < n; i++)
    {
        ln = i * avg - sum;
        sum += mh[i];
        // (n - i - 1) * avg - sum - (n * avg - sum)
        rn = sum - (i + 1) * avg;
        if (ln > 0 && rn > 0)
        {
            ans = max(ans, ln + rn);
        }
        else
        {
            ans = max(ans, max(abs(ln), abs(rn)));
        }
    }

    return ans;
}