#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <array>
#include <climits>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
#define ll long long
ll moves[] = {-1, 0, 1, 0, -1};

ll manha(ll x1, ll y1, ll x2, ll y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}
ll shev(ll x1, ll y1, ll x2, ll y2)
{
    return max(abs(x2 - x1), abs(y2 - y1));
}
double euclidean(ll x1, ll y1, ll x2, ll y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

struct comp
{
    bool operator()(const vector<ll> &a, const vector<ll> &b) const
    {
        return a[2] > b[2];
    }
};
ll astar(vector<vector<ll>> &grid, ll sx, ll sy, ll tx, ll ty)
{
    // grid[sx][sy] = 0 || grid[tx][ty] = 0, return -1

    ll n = grid.size(), m = grid[0].size();
    ll dist[101][101];
    bool vis[101][101];
    memset(vis, 0, sizeof(vis));
    memset(dist, 999, sizeof(dist));
    dist[sx][sy] = 1;

    priority_queue<vector<ll>, vector<vector<ll>>, comp> pq;

    ll h_cost = manha(sx, sy, tx, ty);
    pq.push({sx, sy, 1 + h_cost});
    while (!pq.empty())
    {
        vector<ll> cur = pq.top();
        pq.pop();
        ll x = cur[0];
        ll y = cur[1];

        if (vis[x][y])
        {
            continue;
        }
        vis[x][y] = true;

        if (x != tx || y != ty)
        {
            for (ll i = 0; i < 4; ++i)
            {
                ll nx = x + moves[i];
                ll ny = y + moves[i + 1];

                if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                    grid[nx][ny] && !vis[nx][ny] &&
                    dist[x][y] + 1 < dist[nx][ny])
                {
                    dist[nx][ny] = dist[x][y] + 1;
                    ll nh_cost = manha(nx, ny, tx, ty);
                    pq.push({nx, ny, dist[nx][ny] + nh_cost});
                }
            }
        }
        else
        {
            return dist[x][y];
        }
    }
    return -1;
}
