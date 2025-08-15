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

// shortest substring that covers all characters of a target string tar (order doesn't matter).
string sho_tar(string str, string tar)
{
    ll debt = tar.length();
    unordered_map<char, ll> mp;
    for (char ch : tar)
    {
        mp[ch]--;
    }

    ll s = 0, len = LLONG_MAX;
    for (ll l = 0, r = 0; r < str.length(); r++)
    {
        mp[str[r]]++;
        if (mp[str[r]] <= 0)
        {
            debt--;
        }

        if (debt == 0)
        {
            while (mp[str[l]] > 0)
            {
                mp[str[l++]]--;
            }

            if (r - l + 1 < len)
            {
                len = r - l + 1;
                s = l;
            }
        }
    }
    return len != LLONG_MAX ? str.substr(s, len) : "";
}

// circular array of length n, find any starting point such that all prefix sums of the n-1 elements following it are greater than 0.
ll cir_pre(ll n)
{
    for (ll l = 0, r = 0, sum; l < n; l = r + 1, r = l)
    {
        // a b c d e  a b c d e
        // 0 1 2 3 4  5 6 7 8 9
        // l     r       [l, r)
        sum = 0;
        while (sum + arr[r % n] >= 0)
        {
            if (r - l + 1 == n)
            {
                return l;
            }
            sum += arr[r % n];
            r++;
        }
    }
    return -1;
}

// string length n (n % 4 = 0), composed of 'Q', 'W', 'E', and 'R', it is considered balanced if each character appears n/4 times.
// the minimum length of a substring that needs to be replaced to make the string balanced.
string bal_str(string str)
{
    ll n = str.length();
    // Q  W  E  R  n = 40
    // 4 12 14 10  →  the shortest substr to cover 2W and 4E

    ll debt = 0;
    unordered_map<char, ll> mp, num;
    for (char ch : str)
    {
        num[ch]++;
    }

    ll bal = n / 4;
    for (pair<char, ll> p : num)
    {
        if (p.second > bal)
        {
            debt += (p.second - bal);
            mp[p.first] = bal - p.second;
        }
    }

    if (!debt)
    {
        return "";
    }

    ll s = 0, len = LLONG_MAX;
    for (ll l = 0, r = 0; r < str.length(); r++)
    {
        mp[str[r]]++;
        if (mp[str[r]] <= 0)
        {
            debt--;
        }

        if (debt == 0)
        {
            while (mp[str[l]] > 0)
            {
                mp[str[l++]]--;
            }

            if (r - l + 1 < len)
            {
                len = r - l + 1;
                s = l;
            }
        }
    }
    return len != LLONG_MAX ? str.substr(s, len) : "";
}

// the number of subarrays with at most k distinct numbers.
ll f(ll k, ll n)
{
    if (k == 0)
    {
        return 0;
    }

    ll ans = 0;
    unordered_map<ll, ll> mp;
    for (ll l = 0, r = 0, dist = 0; r < n; r++)
    {
        if (++mp[arr[r]] == 1)
        {
            dist++;
        }

        while (dist > k)
        {
            if (--mp[arr[l++]] == 0)
            {
                dist--;
            }
        }

        ans += (r - l + 1);
    }

    return ans;
}
// the number of subarrays where the count of distinct numbers equals k → dis_k = f(k) - f(k-1).
ll dis_k(ll k, ll n)
{
    return f(k, n) - f(k - 1, n);
}

// longest substring where every character appears at least k times (a~z).
ll cha_k(string str, ll k)
{
    unordered_map<char, ll> mp;
    ll ans = 0;
    // under the premise that the substring has exactly require distinct characters, find the longest substring where every character appears at least k times.
    for (ll requ = 1; requ <= 26; requ++)
    {
        mp.clear();
        for (ll l = 0, r = 0, dis = 0, sati = 0; r < str.length(); r++)
        {
            if (++mp[str[r]] == 1)
            {
                dis++;
            }
            if (mp[str[r]] == k)
            {
                sati++;
            }

            while (dis > requ)
            {
                if (mp[str[l]] == 1)
                {
                    dis--;
                }
                if (mp[str[l]] == k)
                {
                    sati--;
                }

                mp[str[l++]]--;
            }

            if (sati == requ)
            {
                ans = max(ans, r - l + 1);
            }
        }
    }
    return ans;
}

// I've found the secret to the sliding window algorithm. It's the relationship between the subarray and monotonicity. As long as there is a monotonic relationship between the length of the subarray and achieving the desired result, you can consider using a sliding window.