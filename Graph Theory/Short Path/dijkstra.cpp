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
vector<vector<pair<ll, ll>>> adj(101);
// without negative edge weights.
// leetcode.cn/problems/network-delay-time/submissions/655555774/
struct comp
{
    bool operator()(const pair<ll, ll> &a, const pair<ll, ll> &b) const
    {
        return a.second > b.second;
    }
};
ll network(vector<vector<ll>> &times, ll n, ll s)
{
    for (vector<ll> &eg : times)
    {
        adj[eg[0]].push_back({eg[1], eg[2]});
    }
    vector<ll> dist(n + 1, inf), vis(n + 1, false);
    dist[s] = 0;

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, comp> pq;
    pq.push({s, 0});

    while (!pq.empty())
    {
        pair<ll, ll> cur = pq.top();
        ll u = cur.first;
        pq.pop();
        if (vis[u])
        {
            continue;
        }
        vis[u] = true;

        for (pair<ll, ll> &eg : adj[u])
        {
            ll v = eg.first, w = eg.second;
            if (!vis[v] && dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({v, dist[v]});
            }
        }
    }

    ll ans = LLONG_MIN;
    for (ll i = 1; i < n + 1; i++)
    {
        if (dist[i] != inf)
        {
            ans = min(ans, dist[i]);
        }
        else
        {
            return -1;
        }
    }
    return ans;
}

// m * logm → m * logn
const ll maxn = 100001;
const ll maxm = 200001;
ll head[maxn], nexe[maxm], to[maxm], weight[maxm];
ll cnt;

// the reverse index table stores the indices of nodes, -1 means never entered the heap, -2 means has already been popped from the heap.
ll heap[maxn], where[maxn];
ll hsize;

ll dist[maxn];
ll n, m, s;

void build()
{
    cnt = 1;
    hsize = 0;
    for (ll i = 1; i < n + 1; ++i)
    {
        head[i] = 0;
        where[i] = -1;
        dist[i] = LLONG_MAX;
    }
}

void add_edge(ll u, ll v, ll w)
{
    nexe[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void swap(ll i, ll j)
{
    ll tmp_node = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp_node;
    where[heap[i]] = i;
    where[heap[j]] = j;
}

void hinsert(ll i)
{
    while (dist[heap[i]] < dist[heap[(i - 1) / 2]])
    {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// the shortest path problem, the value of a node in the min-heap will only be adjusted to a smaller value. Therefore, at this time, only a 'heapify' operation is needed.
void heapify(ll i)
{
    ll l = i * 2 + 1;
    while (l < hsize)
    {
        ll best = l + 1 < hsize && dist[heap[l + 1]] < dist[heap[l]] ? l + 1 : l;
        best = dist[heap[best]] < dist[heap[i]] ? best : i;
        if (best == i)
        {
            break;
        }
        swap(best, i);
        i = best;
        l = i * 2 + 1;
    }
}

ll pop()
{
    ll ans = heap[0];
    swap(0, --hsize);
    heapify(0);
    where[ans] = -2;
    return ans;
}

void update(ll v, ll w)
{
    if (where[v] > -1)
    {
        dist[v] = std::min(dist[v], w);
        hinsert(where[v]);
    }
    else if (where[v] > -2)
    {
        heap[hsize] = v;
        where[v] = hsize++;
        dist[v] = w;
        hinsert(where[v]);
    }
}

void dijkstra()
{
    update(s, 0);
    while (hsize != 0)
    {
        ll v = pop();
        for (ll eid = head[v]; eid > 0; eid = nexe[eid])
        {
            update(to[eid], dist[v] + weight[eid]);
        }
    }
}

// https://leetcode.cn/problems/path-with-minimum-effort/
// At its core, this is a shortest path problem; it's just that the calculation of the path's distance needs to be modified.
struct comp
{
    bool operator()(const vector<ll> &a, const vector<ll> &b) const
    {
        return a[2] > b[2];
    }
};
// nm * lognm
ll min_eff(vector<vector<ll>> &h)
{
    ll n = h.size(), m = h[0].size();
    priority_queue<vector<ll>, vector<vector<ll>>, comp> pq;
    vector<vector<ll>> dist(n, vector<ll>(m, inf));
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    dist[0][0] = 0;
    pq.push({0, 0, 0});

    while (!pq.empty())
    {
        vector<ll> cur = pq.top();
        ll x = cur[0], y = cur[1], d = cur[2];
        pq.pop();

        if (vis[x][y])
        {
            continue;
        }
        vis[x][y] = true;

        if (x != n - 1 || y != m - 1)
        {
            ll move[] = {-1, 0, 1, 0, -1};
            for (ll i = 0; i < 4; i++)
            {
                ll tx = x + move[i], ty = y + move[i + 1];
                if (tx >= 0 && tx < n && ty >= 0 && ty < m && !vis[tx][ty])
                {
                    ll nd = max(d, abs(h[x][y] - h[tx][ty]));
                    if (dist[tx][ty] > nd)
                    {
                        dist[tx][ty] = nd;
                        pq.push({tx, ty, nd});
                    }
                }
            }
        }
        else
        {
            return d;
        }
    }

    return -1;
}