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
const ll MAXN = 11; // n + 1
const ll MAXM = 21; // m + 1 or 2m + 1

ll graph[MAXN][MAXN];
vector<vector<pair<ll, ll>>> adj(MAXN); // vector<vector<ll>> adj, unweighted graph

void build(ll n, vector<vector<ll>> &edges)
{
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            graph[i][j] = 0;
        }
        adj[i].clear();
    }

    for (vector<ll> &e : edges)
    {
        graph[e[0]][e[1]] = e[2];
        adj[e[0]].push_back(make_pair(e[1], e[2]));
    }
}

// Linked Forward Star
// head array is indexed by vertex numbers, starting from 1 whose values are the indices of the head edges.
// nexe, to, and w arrays are all indexed by edge numbers whose values are respectively the index of the next edge, the endpoint of the current edge, and the weight of the current edge.
ll head[MAXN], nexe[MAXM], to[MAXM], wg[MAXM];
ll cnt;
void add_edge(ll u, ll v, ll w)
{
    nexe[cnt] = head[u];
    to[cnt] = v;
    wg[cnt] = w;
    head[u] = cnt++;
}
void build(ll n, vector<vector<ll>> &edges)
{
    cnt = 1;
    memset(head, 0, sizeof(head));

    for (vector<ll> &e : edges)
    {
        ll u = e[0], v = e[1], w = e[2];
        add_edge(u, v, w);
    }
}
void print(ll n)
{
    for (ll i = 1; i <= n; i++)
    {
        for (ll eid = head[i]; eid != 0; eid = nexe[eid])
        {
            cout << i << "→" << to[eid] << ": " << wg[eid] << " | ";
        }
        cout << endl;
    }
}
