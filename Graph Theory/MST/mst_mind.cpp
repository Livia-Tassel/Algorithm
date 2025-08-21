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
const ll MAXN = 5001;
ll root[MAXN];
ll n, cnt;
vector<vector<ll>> adj(MAXN << 1, vector<ll>(3));

void init()
{
    // include virtual source
    for (ll i = 0; i <= n; i++)
    {
        root[i] = i;
    }
    cnt = 0;
}

ll find(ll x)
{
    return root[x] != x ? root[x] = find(root[x]) : x;
}

bool un(ll x, ll y)
{
    ll fx = find(x), fy = find(y);
    if (fx != fy)
    {
        root[fy] = fx;
        return true;
    }
    else
    {
        return false;
    }
}

bool same_set(ll x, ll y)
{
    return find(x) != find(y) ? false : true;
}

// among several villages, there is a cost to build roads connecting them, and a cost to drill a well in each village, how should we plan the drilling of wells and the building of roads to ensure all villages have access to water at the minimum total cost?
ll cost(ll n, vector<ll> &wells, vector<vector<ll>> &pipes)
{
    init();
    for (ll i = 0; i < pipes.size(); i++, cnt++)
    {
        adj[cnt][0] = pipes[i][0];
        adj[cnt][1] = pipes[i][1];
        adj[cnt][2] = pipes[i][2];
    }
    // suppose that there is an edge between the virtual source and each village v, and its weight is the cost to drill a well in village v.
    for (ll i = 0; i < n; i++, cnt++)
    {
        adj[cnt][0] = 0;
        adj[cnt][1] = i + 1;
        adj[cnt][2] = wells[i];
    }

    sort(adj.begin(), adj.begin() + cnt, [](const vector<ll> &a, const vector<ll> &b)
         { return a[2] < b[2]; });

    ll ans = 0;
    for (ll i = 0; i < cnt; i++)
    {
        vector<ll> &edge = adj[i];
        ll u = edge[0], v = edge[1], w = edge[2];
        if (un(u, v))
        {
            ans += w;
        }
    }
    return ans;
}

// some queries [u, v, w] on an undirected graph, return whether there exists a path from u to v where all edge weights on the path are less than w.
vector<bool> dist(ll n, vector<vector<ll>> &adj, vector<vector<ll>> &queries)
{
    ll m = adj.size(), k = queries.size();
    vector<vector<ll>> q(k, vector<ll>(4));
    for (ll i = 0; i < k; i++)
    {
        q[i][0] = queries[i][0];
        q[i][1] = queries[i][1];
        q[i][2] = queries[i][2];
        q[i][3] = i;
    }
    sort(q.begin(), q.end(), [](const vector<ll> &a, const vector<ll> &b)
         { return a[2] < b[2]; });

    sort(adj.begin(), adj.end(), [](const vector<ll> &a, const vector<ll> &b)
         { return a[2] < b[2]; });

    vector<bool> ans(k);
    init();

    for (ll i = 0, j = 0; i < k; i++)
    {
        while (j < m && adj[j][2] < q[i][2])
        {
            vector<ll> &edge = adj[j++];
            ll u = edge[0], v = edge[1], w = edge[2];
            un(u, v);
        }

        ans[q[i][3]] = same_set(q[i][0], q[i][1]);
    }

    return ans;
}

// connected, undirected, weighted graph, select the minimum number of roads to keep all intersections connected, you must also minimize the maximum weight among the selected roads.
// proven that mst is the mbst that this problem asks for, but the reverse is not true.
