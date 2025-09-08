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

// jobs, each with a profit and a required members, the total profit is at least minProfit and the total number of participants is at most n, find the number of different profitable plans.
ll profitable(ll n, ll pt, vl &g, vl &p)
{
}