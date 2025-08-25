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

// 73414494957  →  7449447
// 0090 → 9
string palindromic(string num)
{
    ll cnt[10] = {};
    for (char s : num)
    {
        cnt[s - '0']++;
    }
    ll ans[10001];
    ll ls = 0, mid = 0;

    for (ll i = 9; i > 0; i--)
    {
        if ((cnt[i] & 1) && !mid)
        {
            mid = i;
        }
        for (ll j = cnt[i] / 2; j > 0; j--)
        {
            ans[ls++] = i;
        }
    }

    if (!ls)
    {
        if (mid)
        {
            return to_string(mid);
        }
        else
        {
            return "0";
        }
    }

    for (ll j = cnt[0] / 2; j > 0; j--)
    {
        ans[ls++] = 0;
    }

    bool has_middle = (mid != 0 || (cnt[0] & 1));
    ll len = ls * 2 + (has_middle ? 1 : 0);

    string result(len, ' ');

    for (ll i = 0; i < ls; i++)
    {
        char ch = (char)('0' + ans[i]);
        result[i] = ch;
        result[len - 1 - i] = ch;
    }

    if (has_middle)
    {
        result[ls] = (char)('0' + mid);
    }

    return result;
}

// n workers with their quality and minimum expected wage, hire k workers, where each worker's wage must be proportional to their quality and not less than their minimum expected wage, find the minimum total cost to hire k workers.
struct ly
{
    ll qul;
    ll wg;
    double rate;

    ly(ll q, ll w) : qul(q), wg(w), rate((double)w / q) {}
    bool operator<(const ly &other) const
    {
        return qul < other.qul;
    }
};

double hire(vector<ll> &qul, vector<ll> &wg, ll k)
{
    // align with the lyee who has the highest unit price, otherwise, the requirements will inevitably be violated.
    ll n = qul.size();
    vector<ly> emp;
    for (ll i = 0; i < n; i++)
    {
        emp.push_back(ly(qul[i], wg[i]));
    }
    sort(emp.begin(), emp.end(), [](const ly &a, const ly &b)
         { return a.rate < b.rate; });

    priority_queue<ly> pq;
    ll qsum = 0;
    double ans = 1e12;
    for (ll i = 0; i < n; i++)
    {
        if (pq.size() < k)
        {
            qsum += emp[i].qul;
            pq.push(ly(emp[i].qul, emp[i].wg));
            if (pq.size() >= k)
            {
                ans = min(ans, qsum * emp[i].rate);
            }
        }
        else
        {
            if (emp[i].qul < pq.top().qul)
            {
                qsum += emp[i].qul - pq.top().qul;
                pq.pop();
                pq.push(ly(emp[i].qul, emp[i].wg));
                ans = min(ans, qsum * emp[i].rate);
            }
        }
    }

    return ans;
}

// n trees, each with an initial weight and a daily growth rate, you can cut at most one tree per day for m days, the value of a tree is its initial weight plus its total growth up to that day, find the maximum total value you can obtain over m days.
ll cutting(vector<vector<ll>> &tree, ll n, ll m)
{
    ll dp[251][251];
    memset(dp, 0, sizeof(dp));
    sort(tree.begin() + 1, tree.end(), [](const vector<ll> &a, const vector<ll> &b)
         { return a[1] < b[1]; });

    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < m + 1; j++)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + tree[i][0] + tree[i][1] * (j - 1));
        }
    }

    return dp[n][m];
}