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

    next++;
    dp[i][j] = next;
    return next;
}

// s and t, count the number of times t appears as a subsequence in s.
ll distinct(string s, string t)
{
    ll n = s.length(), m = t.length();
    vvl dp(n + 1, vl(m + 1, 0)); // dp[i][j] → s.substr(0, i) & t.substr(0, j)

    for (ll i = 0; i < n + 1; i++)
    {
        dp[i][0] = 1;
    }
    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < m + 1; j++)
        {
            dp[i][j] = dp[i - 1][j];
            dp[i][j] += (s[i - 1] != t[j - 1] ? 0 : dp[i - 1][j - 1]);
        }
    }

    return dp[n][m];
}

// transform s into t by inserting, deleting, or replacing characters, with each operation having a different cost, find the minimum total cost required.
ll distance(string s, string t, ll a, ll b, ll c)
{
    ll n = s.length(), m = t.length();
    vvl dp(n + 1, vl(m + 1, 0));

    for (ll i = 0; i < n + 1; i++)
    {
        dp[i][0] = i * b;
    }
    for (ll j = 0; j < m + 1; j++)
    {
        dp[0][j] = j * a;
    }

    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < m + 1; j++)
        {
            dp[i][j] = (s[i - 1] != t[j - 1] ? min(min(dp[i - 1][j] + b, dp[i][j - 1] + a), dp[i - 1][j - 1] + c) : dp[i - 1][j - 1]);
        }
    }

    return dp[n][m];
}

// verify if c is an interleaving of a and b.
bool leave(string a, string b, string c)
{
    if (a.length() + b.length() != c.length())
    {
        return false;
    }

    ll n = a.length(), m = b.length();
    vvl dp(n + 1, vl(m + 1, 0)); // dp[i][j] → a.substr(0, i) & b.substr(0, j) → c.substr(0, i+j)

    dp[0][0] = 1;
    for (ll i = 1; i < n + 1; i++)
    {
        if (a[i - 1] != c[i - 1])
        {
            break;
        }
        dp[i][0] = 1;
    }
    for (ll j = 1; j < m + 1; j++)
    {
        if (b[j - 1] != c[j - 1])
        {
            break;
        }
        dp[0][j] = 1;
    }

    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < m + 1; j++)
        {
            dp[i][j] =
                (a[i - 1] == c[i + j - 1] && dp[i - 1][j]) ||
                (b[j - 1] == c[i + j - 1] && dp[i][j - 1]);
        }
    }

    return dp[n][m];
}

// n cells and m colors, color the n cells such that each of the m colors is used at least once, find the total number of valid ways.
ll color(ll n, ll m)
{
    vvl dp(n + 1, vl(m + 1, 0)); // dp[i][j] → i cells, j colors
    for (ll i = 1; i < n + 1; i++)
    {
        dp[i][1] = m;
    }

    for (ll i = 2; i < n + 1; i++)
    {
        for (ll j = 2; j < m + 1; j++)
        {
            dp[i][j] = j * dp[i - 1][j] + (m - j + 1) * dp[i - 1][j - 1];
        }
    }

    return dp[n][m];
}

// the minimum number of characters that must be deleted from s to make it a substring of t.
ll remove(string s, string t)
{
    ll n = s.length(), m = t.length();
    vvl dp(n + 1, vl(m + 1, 0)); // dp[i][j] → s.substr(0, i) be suffix of t.substr(0, j)

    for (ll i = 0; i < n + 1; i++)
    {
        dp[i][0] = i;
    }
    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < m + 1; j++)
        {
            dp[i][j] = (s[i - 1] != t[j - 1] ? dp[i - 1][j] + 1 : dp[i - 1][j - 1]);
        }
    }
    ll ans = LLONG_MAX;
    for (ll j = 0; j < m + 1; j++)
    {
        ans = min(ans, dp[n][j]);
    }
    return ans;
}
