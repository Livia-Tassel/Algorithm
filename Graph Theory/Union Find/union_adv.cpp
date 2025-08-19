#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <map>
#define ll long long
using namespace std;
const ll MAXN = 100001;
ll root[MAXN];
ll n, sets;

ll find(ll x)
{
    return root[x] != x ? root[x] = find(root[x]) : x;
}

void un(ll x, ll y)
{
    ll fx = find(x), fy = find(y);
    if (fx != fy)
    {
        root[fy] = fx;
        sets--;
    }
}

// n stones in a 2d plane, a stone can be removed if there is another stone in the same row or column.
map<ll, ll> col, row;
void build(ll n)
{
    col.clear(), row.clear();
    sets = n;
    for (ll i = 0; i < n; i++)
    {
        root[i] = i;
    }
}
ll rem_ston(vector<vector<ll>> &stones)
{
    //  can be proven that if stones in the same row or column are considered a set, the final answer is the total number of stones minus the number of sets.
    ll n = stones.size();
    build(n);

    for (ll i = 0; i < n; i++)
    {
        ll x = stones[i][0], y = stones[i][1];
        if (!row.count(x))
        {
            row[x] = i;
        }
        else
        {
            un(i, row[x]);
        }

        if (!col.count(y))
        {
            col[y] = i;
        }
        else
        {
            un(i, col[y]);
        }
    }

    return n - sets;
}

// n experts, expert 0 and fp initially know a secret at time 0, the meetings are given as a list meetings[i] = [xi, yi, timei]; the secret spreads through these meetings: if one expert in a meeting knows the secret at timei, the other expert will also learn it.
bool secret[MAXN];
void build(ll n, ll fp)
{
    for (ll i = 0; i < n; i++)
    {
        root[i] = i;
        secret[i] = false;
    }

    root[fp] = 0;
    secret[0] = true;
}
void un(ll x, ll y)
{
    ll fx = find(x), fy = find(y);
    if (fx != fy)
    {
        root[fy] = fx;
        secret[fx] |= secret[fy];
    }
}
vector<ll> fin_peo(ll n, vector<vector<ll>> &meet, ll fp)
{
    build(n, fp);
    sort(meet.begin(), meet.end(), [](const vector<ll> &a, const vector<ll> &b)
         { return a[2] < b[2]; });

    ll m = meet.size();
    for (ll l = 0, r; l < m;)
    {
        r = l;
        while (r + 1 < m && meet[l][2] == meet[r + 1][2])
        {
            r++;
        }

        // the same time
        for (ll i = l; i <= r; i++)
        {
            un(meet[i][0], meet[i][1]);
        }

        for (ll i = l; i <= r; i++)
        {
            ll f = find(meet[i][0]);
            if (!secret[f])
            {
                root[meet[i][0]] = meet[i][0];
                root[meet[i][1]] = meet[i][1];
            }
        }

        l = r + 1;
    }

    vector<ll> ans;
    for (ll i = 0; i < n; i++)
    {
        if (secret[find(i)])
        {
            ans.push_back(i);
        }
    }
    return ans;
}

// given a tree, n nodes, where each node has a value, find the number of "good paths.", good path is defined as a path where :
// 1. the start and end nodes have the same value.
// 2. all intermediate nodes have a value less than or equal to the start / end node's value (path of a single node is also considered a good path).
ll maxcnt[MAXN];
void build(ll n)
{
    for (ll i = 0; i < n; i++)
    {
        root[i] = i;
        maxcnt[i] = 1;
    }
}
ll un(ll x, ll y, vector<ll> &vals)
{
    ll fx = find(x), fy = find(y), path = 0;
    if (vals[fx] > vals[fy])
    {
        root[fy] = fx;
    }
    else if (vals[fx] < vals[fy])
    {
        root[fx] = fy;
    }
    else
    {
        path = maxcnt[fx] * maxcnt[fy];
        root[fy] = fx;
        maxcnt[fx] += maxcnt[fy];
    }
    return path;
}
ll paths(vector<ll> &vals, vector<vector<ll>> &edges)
{
    ll n = vals.size();
    build(n);
    ll ans = n;
    sort(edges.begin(), edges.end(), [&vals](const vector<ll> &a, const vector<ll> &b)
         { return max(vals[a[0]], vals[a[1]]) < max(vals[b[0]], vals[b[1]]); });

    for (const vector<ll> &e : edges)
    {
        ans += un(e[0], e[1], vals);
    }
    return ans;
}

// given a graph and a set of initially infected nodes, an infection spreads along connections, remove one initially infected node to minimize the final number of infected nodes, if there is a tie, return the node with the smallest index.
bool virus[MAXN];
// cnts records how many nodes can be saved by deleting each source virus.
// infect[x] equals -1, means no virus; greater than or equal to 0, represents the virus index; equals - 2, means two or more source viruses.
ll cnts[MAXN], infect[MAXN], size[MAXN];
void un(ll x, ll y)
{
    ll fx = find(x), fy = find(y);
    if (fx != fy)
    {
        root[fy] = fx;
        size[fx] += size[fy];
    }
}
void build(ll n, vector<ll> &init)
{
    for (ll i = 0; i < n; i++)
    {
        virus[i] = false;
        cnts[i] = 0;
        infect[i] = -1;
        size[i] = 1;
        root[i] = i;
    }

    for (ll x : init)
    {
        virus[x] = true;
    }
}
ll spread(vector<vector<ll>> &graph, vector<ll> &init)
{
    ll n = graph.size();
    build(n, init);

    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            if (graph[i][j] && !virus[i] && !virus[j])
            {
                un(i, j);
            }
        }
    }

    for (ll sick : init)
    {
        ll neigh;
        for (ll i = 0; i < n; i++)
        {
            if (graph[sick][i] && sick != i && !virus[i])
            {
                neigh = i;
                ll fn = find(neigh);
                if (infect[fn] == -1)
                {
                    infect[fn] = sick;
                }
                else if (infect[fn] != -2 && infect[fn] != sick)
                {
                    infect[fn] = -2;
                }
            }
        }
    }

    for (ll i = 0; i < n; i++)
    {
        if (find(i) == i && !virus[i] && infect[i] >= 0)
        {
            cnts[infect[i]] += size[i];
        }
    }

    sort(init.begin(), init.end());
    ll max = cnts[init[0]], pos = init[0];

    for (ll v : init)
    {
        if (cnts[v] > max)
        {
            max = cnts[v];
            pos = v;
        }
    }

    return pos;
}