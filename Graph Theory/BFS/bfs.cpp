#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <set>
#define ll long long
using namespace std;

// distance of the farthest ocean cell ('0') from land ('1').
ll dist(vector<vector<ll>> &grid)
{
    ll n = grid.size(), m = grid[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<pair<ll, ll>> q(n * m);
    ll move[] = {-1, 0, 1, 0, -1};

    ll l = 0, r = 0, seas = 0;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (grid[i][j] != 1)
            {
                seas++;
            }
            else
            {
                vis[i][j] = true;
                q[r].first = i;
                q[r++].second = j;
            }
        }
    }

    ll level = 0, size;
    while (l < r)
    {
        level++;
        size = r - l;
        for (ll i = 0, tx, ty; i < size; i++)
        {
            pair<ll, ll> cur = q[l++];
            for (ll j = 0; j < 4; j++)
            {
                tx = cur.first + move[j];
                ty = cur.second + move[j + 1];
                if (tx >= 0 && tx < n && ty >= 0 && ty < m && !vis[tx][ty])
                {
                    vis[tx][ty] = true;
                    q[r].first = tx;
                    q[r++].second = ty;
                }
            }
        }
    }

    return level - 1;
}

// target string and a list of sticker words, find the minimum number of stickers required to spell the target string, you can use letters from the stickers, and each sticker is available in unlimited supply.
string str_sub(const string &cur, const string &s)
{
    unordered_map<char, ll> s_cnt;
    for (char c : s)
    {
        s_cnt[c]++;
    }

    string result = "";

    for (char c : cur)
    {
        if (s_cnt.count(c) && s_cnt[c] > 0)
        {
            s_cnt[c]--;
        }
        else
        {
            result += c;
        }
    }

    return result;
}
ll stickers(vector<string> &st, string tar)
{
    // branch pruning
    vector<vector<string>> graph(26);
    for (string &s : st)
    {
        sort(s.begin(), s.end());
        for (ll i = 0; i < s.length(); i++)
        {
            if (i < 1 || s[i] != s[i - 1])
            {
                graph[s[i] - 'a'].push_back(s);
            }
        }
    }

    set<string> vis;
    sort(tar.begin(), tar.end());
    vector<string> q(1001);
    ll l = 0, r = 0, level = 1, size;
    q[r++] = tar;
    vis.insert(tar);
    while (l < r)
    {
        size = r - l;
        for (ll i = 0; i < size; i++)
        {
            string cur = q[l++];
            for (string &s : graph[cur[0] - 'a'])
            {
                string cur_s = str_sub(cur, s);
                if (cur_s.empty())
                {
                    return level;
                }
                else if (!vis.count(cur_s))
                {
                    vis.insert(cur_s);
                    q[r++] = cur_s;
                }
            }
        }
        level++;
    }

    return -1;
}