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

// Bellman-Ford O(m*n)
ll price(ll n, vector<vector<ll>> &flights, ll src, ll dst, ll k)
{
    vector<ll> cur(n, inf);
    cur[src] = 0;
    for (ll i = 0; i < k + 1; i++)
    {
        vector<ll> next(cur);
        for (vector<ll> &eg : flights)
        {
            ll u = eg[0], v = eg[1], w = eg[2];
            if (cur[u] != inf)
            {
                next[v] = min(next[v], cur[u] + w);
            }
        }
        cur = next;
    }
    return cur[dst] != inf ? cur[dst] : -1;
}

// SPFA
const ll maxn = 2001, maxm = 6001, maxq = 4000001;
ll head[maxn], nexe[maxm], to[maxm], wg[maxm];
ll cnt;
void add_edge(ll u, ll v, ll w)
{
    nexe[cnt] = head[u];
    to[cnt] = v;
    wg[cnt] = w;
    head[u] = cnt++;
}

ll dist[maxn], u_cnt[maxn], q[maxq];
bool enter[maxn];
ll l, r;
void build(ll n)
{
    cnt = 1;
    memset(head, 0, sizeof(head));

    l = 0, r = 0;
    for (int i = 0; i < n + 1; ++i)
    {
        dist[i] = inf;
    }
    memset(u_cnt, 0, sizeof(u_cnt));
    memset(enter, 0, sizeof(enter));
}

bool spfa(ll s, ll n)
{
    dist[s] = 0;
    u_cnt[s]++;
    q[r++] = s;
    enter[s] = true;
    while (l < r)
    {
        ll u = q[l++];
        enter[u] = false;
        for (ll eid = head[u], v, w; eid > 0; eid = nexe[eid])
        {
            v = to[eid], w = wg[eid];
            if (dist[u] != inf && dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                if (!enter[v])
                {
                    if (++u_cnt[v] >= n)
                    {
                        return true;
                    }
                    q[r++] = v;
                    enter[v] = true;
                }
            }
        }
    }
    return false;
}
signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        ll n, m, u, v, w;
        cin >> n >> m;
        build(n);
        for (ll i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            if (w >= 0)
            {
                add_edge(v, u, w);
            }
            add_edge(u, v, w);
        }
        cout << spfa(1, n) ? "Yes" : "No";
    }
}