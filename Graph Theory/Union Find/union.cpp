#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <cstdlib>
#define ll long long
using namespace std;
const ll MAXN = 100001;
ll root[MAXN], size[MAXN], st[MAXN];
ll n, sets;

void init()
{
    for (ll i = 0; i < n; i++)
    {
        root[i] = i, size[i] = 1;
    }
}

ll find(ll x)
{
    // return root[x] != x ? root[x] = find(root[x]) : x;

    ll size = 0;
    while (x != root[x])
    {
        st[size++] = x;
        x = root[x];
    }

    while (size > 0)
    {
        root[st[--size]] = x;
    }

    return x;
}

void un(ll x, ll y)
{
    ll fx = find(x), fy = find(y);
    if (fx != fy)
    {
        if (size[fy] > size[fx])
        {
            root[fx] = fy;
            size[fy] += size[fx];
        }
        else
        {
            root[fy] = fx;
            size[fx] += size[fy];
        }
        sets--;
    }
}

// n couples, a total of 2n people (0 and 1 are a couple, 2 and 3 are a couple, and so on), sitting in seats numbered 0 to 2n-1, return minimum number of swaps required to make all couples sit side by side.
ll couples(vector<ll> &row)
{
    ll ans = 0;
    n = row.size() / 2;
    init();

    for (ll i = 0; i / 2 < n; i += 2)
    {
        un(row[i] / 2, row[i + 1] / 2);
    }

    for (ll x = 0; x < n; x++)
    {
        ll fx = root[x];
        ans += (fx != x ? 0 : (size[x] - 1));
    }

    return ans;
}

// 2d grid composed of '1's (land) and '0's (water), calculate the number of islands in the grid.
void build(ll n, ll m, vector<vector<char>> &grid)
{
    sets = 0;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (grid[i][j] == '1')
            {
                ll x = i * m + j;
                root[x] = x;
                sets++;
            }
        }
    }
}
ll lands(vector<vector<char>> &grid)
{
    ll n = grid.size(), m = grid[0].size();
    build(n, m, grid);

    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (grid[i][j] == '1')
            {
                if (j > 0 && grid[i][j - 1] == '1')
                {
                    ll x = i * m + j;
                    ll y = i * m + (j - 1);
                    un(x, y);
                }
                if (i > 0 && grid[i - 1][j] == '1')
                {
                    ll x = i * m + j;
                    ll y = (i - 1) * m + j;
                    un(x, y);
                }
            }
        }
    }

    return sets;
}