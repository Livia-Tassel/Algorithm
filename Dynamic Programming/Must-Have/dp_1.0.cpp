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

// array of travel days and the costs of three types of passes with different durations (1, 7, 30), find the minimum total cost to cover all the specified travel days.
vl dur = {1, 7, 30};
vl dp(366, -1);
ll f(vl &days, vl &costs, ll i, ll n)
{
    if (i == n)
    {
        return 0;
    }

    if (dp[i] != -1)
    {
        return dp[i];
    }

    ll ans = LLONG_MAX;
    for (ll k = 0, j = i; k < 3; k++)
    {
        while (j < n && dur[k] + days[i] > days[j])
        {
            j++;
        }
        ans = min(ans, costs[k] + f(days, costs, j, n));
    }

    dp[i] = ans;
    return ans;
}
ll tickets(vl &days, vl &costs)
{
    ll n = days.size();
    return f(days, costs, 0, n);
}

// string s of digits, where letters A-Z are mapped to numbers 1-26, find the total number of ways to decode s into a sequence of letters.
// ll f(string &s, ll i)
// {
//     ll n = s.length();
//     if (i == n)
//     {
//         return 1;
//     }

//     ll ans;
//     if (s[i] == '0')
//     {
//         ans = 0;
//     }
//     else
//     {
//         ans = f(s, i + 1);
//         if (i + 1 < n && 10 * (s[i] - '0') + (s[i + 1] - '0') < 27)
//         {
//             ans += f(s, i + 2);
//         }
//     }

//     return ans;
// }
ll decodings(string s)
{
    // f(s, 0);
    ll n = s.length();
    vl dp(n + 1);
    dp[n] = 1;

    for (ll i = n - 1; i >= 0; i--)
    {
        if (s[i] == '0')
        {
            dp[i] = 0;
        }
        else
        {
            dp[i] = dp[i + 1];
            if (i + 1 < n && 10 * (s[i] - '0') + (s[i + 1] - '0') < 27)
            {
                dp[i] += dp[i + 2];
            }
        }
    }

    return dp[0];
}
// decodings-2.0, string s of digits and *, * can represent any digit from 1 to 9.

// return the n-th ugly number, which is a positive integer whose only prime factors are 2, 3, or 5.
ll ugly(ll n)
{
    vl dp(n + 1);
    dp[1] = 1;

    for (ll i = 2, pto = 1, pte = 1, pfv = 1, to, te, fv; i < n + 1; i++)
    {
        to = 2 * dp[pto];
        te = 3 * dp[pte];
        fv = 5 * dp[pfv];
        ll min = std::min(to, std::min(te, fv));

        min != to ?: pto++;
        min != te ?: pte++;
        min != fv ?: pfv++;

        dp[i] = min;
    }

    return dp[n];
}

// string containing only '(' and ')', find the length of the longest valid parenthesis substring.
ll parentheses(string s)
{
    ll ans = 0, n = s.length();
    vl dp(n, 0);

    for (ll i = 1, p; i < n; i++)
    {
        if (s[i] != '(')
        {
            p = i - dp[i - 1] - 1;
            if (p >= 0 && s[p] == '(')
            {
                dp[i] = dp[i - 1] + 2 + (p > 0 ? dp[p - 1] : 0);
            }
        }
        ans = max(ans, dp[i]);
    }

    return ans;
}

// string s, count and return how many different non-empty substrings of s also appear in an infinitely repeating string base of the alphabet.
// base: ...abcdefg...xyzabcdefg...
ll wrapround(string s)
{
    ll ans = 0, n = s.length();
    vl dp(26, 0);
    dp[s[0] - 'a'] = 1;

    for (ll i = 1, len = 1; i < n; i++)
    {
        ll ch = s[i] - 'a';
        (s[i] - s[i - 1] + 26) % 26 != 1 ? len = 1 : len++;
        dp[ch] = max(dp[ch], len);
    }

    for (ll num : dp)
    {
        ans += num;
    }
    return ans;
}

// string s, count the number of different non-empty subsequences.
// abc → {a}, {b}, {c}, {ab}, {ac}, {bc}
const ll mod = 1e9 + 7;
ll distinct(string s)
{
    vl cnt(26, 0);
    ll all = 1, nadd;
    for (char x : s)
    {
        nadd = (all - cnt[x - 'a'] + mod) % mod;
        all = (all + nadd) % mod;
        cnt[x - 'a'] = (cnt[x - 'a'] + nadd) % mod;
    }

    return (all - 1 + mod) % mod;
}