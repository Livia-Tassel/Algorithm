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
using vs = vector<string>;
using vvvd = vector<vector<vector<double>>>;
using vvvl = vector<vector<vector<ll>>>;
using vvd = vector<vector<double>>;
using vd = vector<double>;
const ll mod = 1e9 + 7;

// binary strings strs, find the maximum size of a subset of strs such that the total number of '0's is at most m and the total number of '1's is at most n.
ll o, t;
void count(string str)
{
    o = 0;
    t = 0;
    for (ll i = 0; i < str.length(); i++)
    {
        str[i] != '0' ? t++ : o++;
    }
}
ll form(vs &strs, ll m, ll n)
{
    // ll dp[len + 1][m + 1][n + 1]; // strs[k,...], i 0, j 1
    vvl dp(m + 1, vl(n + 1, 0));
    for (string str : strs)
    {
        count(str);
        for (ll i = m; i + 1 > o; i--)
        {
            for (ll j = n; j + 1 > t; j--)
            {
                dp[i][j] = max(dp[i][j], 1 + dp[i - o][j - t]);
            }
        }
    }

    return dp[m][n];
}

// m jobs, each with a profit and a required members, the total profit is at least minProfit and the total number of participants is at most n, find the number of different profitable plans.
ll profitable(ll n, ll m, ll pt, vl &g, vl &p)
{
    vvl dp(n + 1, vl(pt + 1));
    for (ll r = 0; r < n + 1; r++)
    {
        dp[r][0] = 1;
    }

    for (ll i = m - 1; i > -1; i--)
    {
        for (ll r = n; r > -1; r--)
        {
            for (ll s = pt; s > -1; s--)
            {
                ll pp = g[i] < r + 1 ? dp[r - g[i]][max((ll)0, s - p[i])] : 0;
                dp[r][s] = (pp + dp[r][s]) % mod;
            }
        }
    }
    return dp[n][pt];
}

// n x n chessboard, a knight starts at (row, col) and makes k moves, each move, the knight randomly chooses one of the 8 possible moves, find the probability that the knight remains on the board after k moves.
double f(ll n, ll i, ll j, ll k, vvvd &dp)
{
    if (i < 0 || i > n - 1 || j < 0 || j > n - 1)
    {
        return 0;
    }
    if (dp[i][j][k] != -1)
    {
        return dp[i][j][k];
    }
    double ans = 0;
    if (k == 0)
    {
        ans = 1;
    }
    else
    {
        ans += (f(n, i - 2, j + 1, k - 1, dp) / 8);
        ans += (f(n, i - 1, j + 2, k - 1, dp) / 8);
        ans += (f(n, i + 1, j + 2, k - 1, dp) / 8);
        ans += (f(n, i + 2, j + 1, k - 1, dp) / 8);
        ans += (f(n, i + 2, j - 1, k - 1, dp) / 8);
        ans += (f(n, i + 1, j - 2, k - 1, dp) / 8);
        ans += (f(n, i - 1, j - 2, k - 1, dp) / 8);
        ans += (f(n, i - 2, j - 1, k - 1, dp) / 8);
    }
    dp[i][j][k] = ans;
    return ans;
}
double knight(ll n, ll k, ll row, ll col)
{
    vvvd dp(n, vvd(n, vd(k + 1, -1)));
    return f(n, row, col, k, dp);
}

// n x m grid and k, you can only move down or right from the top-left to the bottom-right, find the number of paths where the sum of the numbers along the path is divisible by k.
ll paths(vvl &grid, ll k, ll n, ll m)
{
    vvvl dp(n, vvl(m, vl(k, 0)));
    dp[n - 1][m - 1][grid[n - 1][m - 1] % k] = 1;

    for (ll i = n - 2; i > -1; i--)
    {
        for (ll r = 0; r < k; r++)
        {
            dp[i][m - 1][r] = dp[i + 1][m - 1][(k + r - grid[i][m - 1] % k) % k];
        }
    }
    for (ll j = m - 2; j > -1; j--)
    {
        for (ll r = 0; r < k; r++)
        {
            dp[n - 1][j][r] = dp[n - 1][j + 1][(k + r - grid[n - 1][j] % k) % k];
        }
    }
    for (ll i = n - 2, need; i > -1; i--)
    {
        for (ll j = m - 2; j > -1; j--)
        {
            for (ll r = 0; r < k; r++)
            {
                need = (k + r - grid[i][j] % k) % k;
                dp[i][j][r] = dp[i + 1][j][need];
                dp[i][j][r] = (dp[i][j][r] + dp[i][j + 1][need]) % mod;
            }
        }
    }
    return dp[0][0][0];
}

// https://leetcode.cn/problems/scramble-string/
bool scramble(string s, string t)
{
    ll n = s.length();
    vvvl dp(n, vvl(n, vl(n + 1, 0)));

    for (ll l1 = 0; l1 < n; l1++)
    {
        for (ll l2 = 0; l2 < n; l2++)
        {
            dp[l1][l2][1] = (s[l1] != t[l2] ? 0 : 1);
        }
    }
    for (ll len = 2; len < n + 1; len++)
    {
        for (ll l1 = 0; l1 < n + 1 - len; l1++)
        {
            for (ll l2 = 0; l2 < n + 1 - len; l2++)
            {
                for (ll k = 1; k < len; k++)
                {
                    if (dp[l1][l2][k] && dp[l1 + k][l2 + k][len - k])
                    {
                        dp[l1][l2][len] = 1;
                        break;
                    }
                }
                if (!dp[l1][l2][len])
                {
                    for (ll i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++)
                    {
                        if (dp[l1][j][k] && dp[i][l2][len - k])
                        {
                            dp[l1][l2][len] = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    return dp[0][0][n];
}