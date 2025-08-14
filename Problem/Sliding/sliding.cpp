#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#define ll long long
using namespace std;
const ll MAXN = 1001;
vector<ll> arr(MAXN);

// shortest subarray with a sum greater than or equal to target. (arr[i] > 0)
ll min_len(ll target, ll n)
{
    ll ans = LLONG_MAX;
    for (ll l = 0, r = 0, sum = 0; r < n; r++)
    {
        sum += arr[r];
        while (sum - arr[l] >= target)
        {
            sum -= arr[l++];
        }

        if (sum >= target)
        {
            ans = min(ans, r - l + 1);
        }
    }
    return ans != LLONG_MAX ? ans : 0;
}

// longest substring without repeating characters.
ll lon_cha(string s)
{
    ll ans = 0;
    map<char, ll> mp;

    for (ll l = 0, r = 0; r < s.length(); r++)
    {
        if (mp.count(s[r]))
        {
            l = max(l, mp[s[r]] + 1);
        }
        ans = max(ans, r - l + 1);
        mp[s[r]] = r;
    }

    return ans;
}