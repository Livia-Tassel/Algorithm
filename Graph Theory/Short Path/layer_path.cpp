#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <unordered_set>
#include <deque>
#define ll long long
using namespace std;
const ll inf = 9999;
// grid containing empty rooms, walls, a start point '@', lowercase letter keys, and their corresponding uppercase locks, find the minimum number of moves to collect all keys starting from the initial position; you can pick up keys, but you can only pass through a lock if you have the matching key, return -1 if it is impossible to collect all keys.
const ll maxn = 31, maxm = 31, maxk = 1 << 6;
bool vis[maxn][maxm][maxk];
ll q[maxn * maxm * maxk][3];
ll l, r, n, m, key;
void build(vector<string> &grid)
{
    memset(vis, 0, sizeof(vis));
    l = 0, r = 0, key = 0;
    n = grid.size(), m = grid[0].size();

    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (grid[i][j] == '@')
            {
                q[r][0] = i;
                q[r][1] = j;
                q[r++][2] = 0; // 000000
            }
            if (grid[i][j] >= 'a' && grid[i][j] < 'g')
            {
                key |= 1 << (grid[i][j] - 'a');
            }
        }
    }
}
ll sho_keys(vector<string> &grid)
{
    // . . @ #
    // b B . a
    build(grid);
    ll move[] = {-1, 0, 1, 0, -1};
    ll level = 1;
    while (l < r)
    {
        ll size = r - l;
        for (ll k = 0; k < size; k++)
        {
            ll x = q[l][0], y = q[l][1];
            ll sta = q[l++][2];
            for (ll i = 0; i < 4; i++)
            {
                ll tx = x + move[i], ty = y + move[i + 1], nsta = sta;
                if (tx < 0 || tx >= n || ty < 0 || ty >= m || grid[tx][ty] == '#')
                {
                    continue;
                }
                // check key
                if ((grid[tx][ty] >= 'A' && grid[tx][ty] < 'G') && ((nsta & (1 << (grid[tx][ty] - 'A'))) == 0))
                {
                    continue;
                }

                if (grid[tx][ty] >= 'a' && grid[tx][ty] < 'g')
                {
                    nsta |= 1 << (grid[tx][ty] - 'a');
                }

                if (nsta != key)
                {
                    if (!vis[tx][ty][nsta])
                    {
                        vis[tx][ty][nsta] = true;
                        q[r][0] = tx;
                        q[r][1] = ty;
                        q[r++][2] = nsta;
                    }
                }
                else
                {
                    return level;
                }
            }
        }
        level++;
    }
    return -1;
}

// electric scooter has a max power of cnt, there are n cities on a map with bidirectional roads, starting with 0 power, each city has a different time cost to charge, find the minimum total time required to travel from a starting city to an ending city, including both travel and charging time.
struct comp
{
    bool operator()(const vector<ll> &a, const vector<ll> &b) const
    {
        return a[2] > b[2];
    }
};
// O((n+m)⋅cnt⋅log(n⋅cnt))
ll electric(vector<vector<ll>> &paths, ll cnt, ll start, ll end, vector<ll> &charge)
{
    ll n = charge.size();
    vector<vector<pair<ll, ll>>> adj(101);
    for (vector<ll> &path : paths)
    {
        ll u = path[0], v = path[1], w = path[2];
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    ll dist[101][101]; // dist[n][cnt+1]
    bool vis[101][101];
    memset(vis, 0, sizeof(vis));
    memset(dist, inf, sizeof(dist));
    dist[start][0] = 0;

    priority_queue<vector<ll>, vector<vector<ll>>, comp> pq;
    pq.push({start, 0, 0});

    while (!pq.empty())
    {
        vector<ll> ct = pq.top();
        ll pos = ct[0], pow = ct[1], cost = ct[2];
        pq.pop();

        if (vis[pos][pow])
        {
            continue;
        }
        vis[pos][pow] = true;

        if (pos != end)
        {
            if (pow < cnt)
            {
                if (!vis[pos][pow + 1] && dist[pos][pow + 1] > cost + charge[pos])
                {
                    dist[pos][pow + 1] = cost + charge[pos];
                    pq.push({pos, pow + 1, dist[pos][pow + 1]});
                }
            }
            for (pair<ll, ll> &eg : adj[pos])
            {
                ll npos = eg.first, dis = eg.second;
                ll rpow = pow - dis;
                if (rpow >= 0 && !vis[npos][rpow] && dist[npos][rpow] > cost + dis)
                {
                    dist[npos][rpow] = cost + dis;
                    pq.push({npos, rpow, dist[npos][rpow]});
                }
            }
        }
        else
        {
            return cost;
        }
    }
    return -1;
}