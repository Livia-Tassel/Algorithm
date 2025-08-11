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

ll f(ll n)
{
    if (n < 0)
    {
        return LLONG_MAX;
    }
    if (n == 0)
    {
        return 0;
    }

    ll n_8 = f(n - 8);
    ll n_6 = f(n - 6);

    n_8 += (n_8 != LLONG_MAX ? 1 : 0);
    n_6 += (n_6 != LLONG_MAX ? 1 : 0);

    return min(n_6, n_8);
}

// Liu has bags of capacity 8 and 6, a single apple takes up one unit of space, return the minimum number of bags needed for n apples. But, if any bag cannot be completely filled, return -1.
ll min_bags(ll n)
{
    ll ans = f(n);
    return ans == LLONG_MAX ? -1 : ans;
}
void print_bags()
{
    for (ll i = 0; i < 100; i++)
    {
        cout << i << ": " << min_bags(i) << endl;
    }
}

// ------------------------------------------------------------------------------
string f(ll n, string p)
{
    string enemy = (p == "A" ? "B" : "A");

    if (n < 5)
    {
        return (n == 0 || n == 2) ? enemy : p;
    }

    ll pick = 1;
    while (pick <= n)
    {
        if (f(n - pick, enemy) == p)
        {
            return p;
        }
        pick *= 4;
    }
    return enemy;
}

// A (first) and B (second) take turns eating n portions of grass. In each turn, the player can eat 4^i portions of grass. The player who have no grass to eat loses, return the winner.
string eat_grass(ll n)
{
    return f(n, "A");
}
void print_winner()
{
    for (ll i = 0; i < 50; i++)
    {
        cout << i << ": " << eat_grass(i) << endl;
    }
}

// ------------------------------------------------------------------------------
bool is(ll num)
{
    for (ll s = 1, sum; s <= num; s++)
    {
        sum = s;
        for (ll e = s + 1; e <= num; e++)
        {
            if (sum + e > num)
            {
                break;
            }
            if (sum + e == num)
            {
                return true;
            }
            sum += e;
        }
    }
    return false;
}

// Is a number can be partitioned into a sum of several consecutive smaller integers?
bool is_sum(ll n)
{
    return is(n);
}
void print_sum()
{
    for (ll i = 0; i < 200; i++)
    {
        cout << i << ": " << is_sum(i) << endl;
    }
}

// ------------------------------------------------------------------------------
bool is(vector<char> &path, ll l, ll r)
{
    ll m = (l + r) / 2;
    for (; l <= m; l++, r--)
    {
        if (path[l] != path[r])
        {
            return false;
        }
    }

    return true;
}

ll f(vector<char> &path, ll i, ll n)
{
    if (i == n)
    {
        ll cnt = 0;
        for (ll l = 0; l < n; l++)
        {
            for (ll r = l + 1; r < n; r++)
            {
                if (is(path, l, r))
                {
                    cnt++;
                }
            }
        }
        return cnt == 1 ? 1 : 0;
    }
    else
    {
        ll ans = 0;
        path[i] = 'r';
        ans += f(path, i + 1, n);
        path[i] = 'e';
        ans += f(path, i + 1, n);
        path[i] = 'd';
        ans += f(path, i + 1, n);
        return ans;
    }
}

// Nice string means a string has exactly one palindromic substring of length 2 or greater. Now calculate how many 'good strings' of length n can be formed using only the letters r, e, and d.
ll is_string(ll n)
{
    vector<char> path(n);
    return f(path, 0, n);
}
void print_string()
{
    for (ll i = 0; i < 15; i++)
    {
        cout << i << ": " << is_string(i) << endl;
    }
}

signed main()
{
    // print_bags();
    // print_winner();
    print_string();
    return 0;
}