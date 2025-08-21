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
const ll inf = 99999;
// m x n grid of empty cells (0) and obstacles (1), you can move to adjacent empty cells, return the minimum number of obstacles to remove to clear a path from the top-left to the bottom-right corner.
ll obstacles(vector<vector<ll>> &grid)
{
    //  converting moves to obstacles into edges 1, and empty spaces into edges 0, making it a 0-1 bfs problem.
    ll move[] = {-1, 0, 1, 0, -1};
    ll n = grid.size(), m = grid[0].size();
    vector<vector<ll>> dist(n, vector<ll>(m, inf));

    deque<pair<ll, ll>> dq;
    dq.push_back({0, 0});
    dist[0][0] = 0;

    while (!dq.empty())
    {
        pair<ll, ll> cur = dq.front();
        dq.pop_front();
        ll x = cur.first, y = cur.second;

        if (x != n - 1 || y != m - 1)
        {
            for (ll i = 0; i < 4; i++)
            {
                ll tx = x + move[i], ty = y + move[i + 1];
                if (tx >= 0 && tx < n && ty >= 0 && ty < m)
                {
                    if (dist[tx][ty] > dist[x][y] + grid[tx][ty])
                    {
                        dist[tx][ty] = dist[x][y] + grid[tx][ty];
                        if (grid[tx][ty] != 0)
                        {
                            dq.push_back({tx, ty});
                        }
                        else
                        {
                            dq.push_front({tx, ty});
                        }
                    }
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

// 2d trapping rain water problem
struct comp
{
    bool operator()(const vector<ll> &a, const vector<ll> &b) const
    {
        return a[2] > b[2];
    }
};
ll trap_rain(vector<vector<ll>> &h)
{
    ll move[] = {-1, 0, 1, 0, -1};
    ll n = h.size(), m = h[0].size();
    priority_queue<vector<ll>, vector<vector<ll>>, comp> pq;
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (i != 0 && i != n - 1 && j != 0 && j != m - 1)
            {
                vis[i][j] = false;
            }
            else
            {
                pq.push({i, j, h[i][j]});
                vis[i][j] = true;
            }
        }
    }

    ll ans = 0;
    while (!pq.empty())
    {
        vector<ll> cur = pq.top();
        pq.pop();
        ll x = cur[0], y = cur[1], line = cur[2];

        for (ll i = 0; i < 4; i++)
        {
            ll tx = x + move[i], ty = y + move[i + 1];
            if (tx >= 0 && tx < n && ty >= 0 && ty < m && !vis[tx][ty])
            {
                vis[tx][ty] = true;
                pq.push({tx, ty, max(line, h[tx][ty])});
            }
        }

        ans += (line - h[x][y]);
    }
    return ans;
}

// using words from a word list as bridges, starting from ben, change one character at a time to become end, and find all shortest paths.
unordered_set<string> cur_level, next_level;
unordered_map<string, vector<string>> g;
vector<string> path;
vector<vector<string>> ans;

bool bfs(unordered_set<string> &dict, string beg, string end)
{
    bool flag = false;
    cur_level.insert(beg);

    while (!cur_level.empty())
    {
        // branch pruning
        for (const string &word : cur_level)
        {
            dict.erase(word);
        }
        for (string s : cur_level)
        {
            for (ll i = 0; i < s.length(); i++)
            {
                char old = s[i];
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    string str = s;
                    str[i] = ch;
                    if (dict.count(str) && str != s)
                    {
                        if (str == end)
                        {
                            flag = true;
                        }
                        g[str].push_back(s);
                        next_level.insert(str);
                    }
                }
            }
        }

        if (flag)
        {
            return true;
        }
        else
        {
            cur_level = next_level;
            next_level.clear();
        }
    }

    return false;
}
void dfs(unordered_set<string> &dict, string cur, string tar)
{
    path.push_back(cur);
    if (cur == tar)
    {
        vector<string> tmp(path);
        reverse(tmp.begin(), tmp.end());
        ans.push_back(tmp);
    }
    else if (g.count(cur))
    {
        for (string s : g[cur])
        {
            dfs(dict, s, tar);
        }
    }
    path.pop_back();
}
vector<vector<string>> ladders(string beg, string end, vector<string> &list)
{
    unordered_set<string> dict(list.begin(), list.end());

    if (!dict.count(end))
    {
        return ans;
    }

    if (bfs(dict, beg, end))
    {
        dfs(dict, end, beg);
    }

    return ans;
}
