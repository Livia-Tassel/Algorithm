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

// calculate the number of islands in the grid.
void dfs(vector<vector<char>> &grid, ll i, ll j)
{
    ll n = grid.size(), m = grid[0].size();
    if (i < 0 || i > n - 1 || j < 0 || j > m - 1 || grid[i][j] != '1')
    {
        return;
    }
    grid[i][j] = '#';
    dfs(grid, i - 1, j);
    dfs(grid, i + 1, j);
    dfs(grid, i, j - 1);
    dfs(grid, i, j + 1);
}
ll lands(vector<vector<char>> &grid)
{
    ll ans = 0;
    ll n = grid.size(), m = grid[0].size();
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (grid[i][j] == '1')
            {
                ans++;
                dfs(grid, i, j);
            }
        }
    }
    return ans;
}

// x x x x       x x x x
// x o o x   →   x x x x
// o x o x   →   o x x x
// x o x x       x o x x
void dfs(vector<vector<char>> &board, ll i, ll j)
{
    ll n = board.size(), m = board[0].size();
    if (i < 0 || i > n - 1 || j < 0 || j > m - 1 || board[i][j] != 'O')
    {
        return;
    }
    board[i][j] = 'F';
    dfs(board, i - 1, j);
    dfs(board, i + 1, j);
    dfs(board, i, j - 1);
    dfs(board, i, j + 1);
}
void solve(vector<vector<char>> &board)
{
    ll n = board.size(), m = board[0].size();
    // infect from the four borders.
    for (ll i = 0; i < n; i++)
    {
        dfs(board, i, 0);
        dfs(board, i, m - 1);
    }

    for (ll j = 0; j < m; j++)
    {
        dfs(board, 0, j);
        dfs(board, n - 1, j);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            board[i][j] = (board[i][j] != 'F' ? 'X' : 'O');
        }
        cout << endl;
    }
}

// 0 1   →   0 1
// 1 0   →   1 1
// change one position to maximize the area of the largest island.
void dfs(vector<vector<ll>> &grid, ll i, ll j, ll color)
{
    ll n = grid.size(), m = grid[0].size();
    if (i < 0 || i > n - 1 || j < 0 || j > m - 1 || grid[i][j] != 1)
    {
        return;
    }
    grid[i][j] = color;
    dfs(grid, i - 1, j, color);
    dfs(grid, i + 1, j, color);
    dfs(grid, i, j - 1, color);
    dfs(grid, i, j + 1, color);
}
ll larg_land(vector<vector<ll>> &grid)
{
    ll ans = 0, color = 1;
    ll n = grid.size(), m = grid[0].size();
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                dfs(grid, i, j, ++color);
            }
        }
    }

    vector<ll> size(++color, 0);
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (grid[i][j] > 1)
            {
                ans = max(ans, ++size[grid[i][j]]);
            }
        }
    }

    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (grid[i][j] == 0)
            {
                ll area = 1;
                set<ll> neigh;

                if (i > 0 && grid[i - 1][j] > 1)
                    neigh.insert(grid[i - 1][j]);
                if (i < n - 1 && grid[i + 1][j] > 1)
                    neigh.insert(grid[i + 1][j]);
                if (j > 0 && grid[i][j - 1] > 1)
                    neigh.insert(grid[i][j - 1]);
                if (j < m - 1 && grid[i][j + 1] > 1)
                    neigh.insert(grid[i][j + 1]);

                for (ll x : neigh)
                {
                    area += size[x];
                }

                ans = max(ans, area);
            }
        }
    }

    return ans;
}

// m x n grid of bricks (1) and empty spaces (0), bricks are stable if they are connected to the top row or to other stable bricks.
// given a list of hits, remove bricks sequentially, after each removal, count how many bricks fall, return an array of the counts of fallen bricks for each hit.
ll n, m;
ll dfs(vector<vector<ll>> &grid, ll i, ll j)
{
    if (i < 0 || i > n - 1 || j < 0 || j > m - 1 || grid[i][j] != 1)
    {
        return 0;
    }
    grid[i][j] = 2;
    return 1 +
           dfs(grid, i - 1, j) +
           dfs(grid, i + 1, j) +
           dfs(grid, i, j - 1) +
           dfs(grid, i, j + 1);
}
bool worth(vector<vector<ll>> &grid, ll i, ll j)
{
    return (grid[i][j] == 1 && ((i == 0) ||
                                (i > 0 && grid[i - 1][j] == 2) ||
                                (i < n - 1 && grid[i + 1][j] == 2) ||
                                (j > 0 && grid[i][j - 1] == 2) ||
                                (j < m - 1 && grid[i][j + 1] == 2)));
}
vector<ll> hit(vector<vector<ll>> &grid, vector<vector<ll>> &hits)
{
    n = grid.size(), m = grid[0].size();
    ll cnt = hits.size();
    vector<ll> ans(cnt, 0);

    if (n <= 1)
    {
        return ans;
    }

    for (auto &h : hits)
    {
        grid[h[0]][h[1]]--;
    }

    for (ll j = 0; j < m; j++)
    {
        dfs(grid, 0, j);
    }

    for (ll i = cnt - 1; i >= 0; i--)
    {
        ll row = hits[i][0], col = hits[i][1];
        grid[row][col]++;
        if (worth(grid, row, col))
        {
            ans[i] = dfs(grid, row, col) - 1;
        }
    }

    return ans;
}