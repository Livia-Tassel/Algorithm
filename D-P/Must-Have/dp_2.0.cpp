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
using vvc = vector<vector<char>>;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 5;

// m x n mat of non-negative llegers, find a path from the top-left to the bottom-right that minimizes the sum of the numbers along the path, you can only move down or right at each step.
ll path(vvl &mat)
{
    ll n = mat.size(), m = mat[0].size();
    vvl dp(n, vl(m, inf));

    dp[0][0] = mat[0][0];
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (!i && !j)
                continue;
            dp[i][j] = mat[i][j] + min(i > 0 ? dp[i - 1][j] : inf, j > 0 ? dp[i][j - 1] : inf);
        }
    }
    return dp[n - 1][m - 1];
}

// longest common subsequence
ll lcs(string a, string b)
{
    ll n = a.length(), m = b.length();
    vvl dp(n + 1, vl(m + 1, 0));

    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < m + 1; j++)
        {
            dp[i][j] = a[i - 1] != b[j - 1] ? max(dp[i - 1][j], dp[i][j - 1]) : dp[i - 1][j - 1] + 1;
        }
    }

    return dp[n][m];
}

// longest palindrome subsequence (not substring)
// ll lps(string s)
// {
//     string rs(s.rbegin(), s.rend());
//     return lcs(s, rs);
// }
ll lps(string s)
{
    ll n = s.length();
    vvl dp(n, vl(n, 0));

    for (ll l = n - 1; l > -1; l--)
    {
        dp[l][l] = 1;
        if (l + 1 < n)
        {
            dp[l][l + 1] = (s[l] != s[l + 1] ? 1 : 2);
        }
        for (ll r = l + 2; r < n; r++)
        {
            dp[l][r] = s[l] != s[r] ? max(dp[l + 1][r], dp[l][r - 1]) : dp[l + 1][r - 1] + 2;
        }
    }

    return dp[0][n - 1];
}

// count the number of binary trees with n nodes and a height of at most m.
ll tren(ll n, ll m)
{
    vvl dp(n + 1, vl(m + 1, 0));
    for (ll j = 0; j < m; j++)
    {
        dp[0][j] = 1;
    }

    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < m + 1; j++)
        {
            for (ll k = 0; k < i; k++)
            {
                dp[i][j] = (dp[i][j] + dp[k][j - 1] * dp[i - k - 1][j - 1] % mod) % mod;
            }
        }
    }

    return dp[n][m];
}

// m x n lleger matrix, find the length of the longest increasing path.
ll path(vvl &mat)
{
    ll n = mat.size(), m = mat[0].size();
    vvl dp(n, vl(m, 0));
    ll ans = 0;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            ans = max(ans, f(mat, i, j, dp, n, m));
        }
    }
    return ans;
}

ll f(vvl &mat, ll i, ll j, vvl &dp, ll n, ll m)
{
    if (dp[i][j] != 0)
    {
        return dp[i][j];
    }

    ll next = 0;
    if (i > 0 && mat[i][j] < mat[i - 1][j])
    {
        next = max(next, f(mat, i - 1, j, dp, n, m));
    }
    if (i + 1 < n && mat[i][j] < mat[i + 1][j])
    {
        next = max(next, f(mat, i + 1, j, dp, n, m));
    }
    if (j > 0 && mat[i][j] < mat[i][j - 1])
    {
        next = max(next, f(mat, i, j - 1, dp, n, m));
    }
    if (j + 1 < m && mat[i][j] < mat[i][j + 1])
    {
        next = max(next, f(mat, i, j + 1, dp, n, m));
    }

    dp[i][j] = next + 1;
    return next + 1;
}