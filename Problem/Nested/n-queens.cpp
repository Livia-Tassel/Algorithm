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
const ll MAXN = 10001;
ll path[MAXN]; // path stores the columns where queens(rows 0 to i-1) are placed.

bool check_arr(ll i, ll j)
{
    for (ll k = 0; k < i; k++)
    {
        if (path[k] == j || abs(path[k] - j) == abs(k - i))
        {
            return false;
        }
    }
    return true;
}

// i represents the current row, and given a fixed placement of queens(rows 0 to i-1), f_arr returns how many possible placements are there for rows i to n-1?
ll f_arr(ll i, ll n)
{
    if (i == n)
    {
        return 1;
    }

    ll ans = 0;
    for (ll j = 0; j < n; j++)
    {
        if (check_arr(i, j))
        {
            path[i] = j;
            ans += f_arr(i + 1, n);
        }
    }
    return ans;
}

ll f_bin(ll limit, ll col, ll left, ll right)
{
    if (col == limit)
    {
        return 1;
    }

    ll ban = col | left | right;
    ll can = ~ban & limit;

    ll place, ans = 0;
    while (can != 0)
    {
        place = can & (-can);
        can ^= place;
        ans += f_bin(limit, col | place, (left | place) >> 1, (right | place) << 1);
    }
}

ll n_queens(ll n)
{
    if (n < 1)
    {
        return 0;
    }

    // return f_arr(0, n);

    // n = 5, limit = 011111
    ll limit = (1 << n) - 1;
    return f_bin(limit, 0, 0, 0);
}

signed main()
{
    cout << n_queens(8) << endl;
}