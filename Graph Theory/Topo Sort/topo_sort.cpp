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
const ll MAXN = 11;
const ll MAXM = 21;

// topo-sort
vector<ll> topo(ll n, vector<vector<ll>> &pre)
{
    vector<ll> deg(n, 0), q(n);
    vector<vector<ll>> adj(n);

    for (vector<ll> &e : pre)
    {
        // e[1] → e[0]
        adj[e[1]].push_back(e[0]);
        deg[e[0]]++;
    }

    ll l = 0, r = 0;
    for (ll i = 0; i < n; i++)
    {
        deg[i] != 0 ?: q[r++] = i;
    }

    ll cnt = 0;
    while (l < r)
    {
        ll cur = q[l++];
        cnt++;
        for (ll next : adj[cur])
        {
            --deg[next] != 0 ?: q[r++] = next;
        }
    }

    vector<ll> null;
    return cnt != n ? null : q;
}

// lexicographically smallest topological sort.
ll head[MAXN], nexe[MAXM], to[MAXM];
ll cnt;
void add_edge(ll u, ll v)
{
    nexe[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

priority_queue<ll, vector<ll>, greater<ll>> pq;
vector<ll> deg(MAXN, 0);
void build(vector<vector<ll>> &edges)
{
    cnt = 1;
    memset(head, 0, sizeof(head));

    for (vector<ll> &e : edges)
    {
        ll u = e[0], v = e[1];
        add_edge(u, v);
        deg[v]++;
    }
}
void topo_lex(ll n, vector<vector<ll>> &pre)
{
    build(pre);

    for (ll i = 1; i < n + 1; i++)
    {
        if (deg[i] == 0)
        {
            pq.push(i);
        }
    }

    while (!pq.empty())
    {
        ll cur = pq.top();
        pq.pop();
        cout << cur << " ";
        for (ll eid = head[cur]; eid != 0; eid = nexe[eid])
        {
            if (--deg[to[eid]] == 0)
            {
                pq.push(to[eid]);
            }
        }
    }
}

// st = abc, tar = aabcbc
// ??????  →  abc???  →  abcabc  →  aabcbc, return [0, 3, 1]
// 0: √ × ×  →  2       →  0  pop
//   1: √ √ √  →  0  pop
//     2: × × ×  →  3       →  1       →  0  pop
//       3: × √ √  →  1       →  0  pop
// return [2, 3, 0, 1]
vector<ll> stamp(string st, string tar)
{
    ll m = st.length(), n = tar.length();
    vector<ll> deg(n - m + 1, m), q(n - m + 1), path;
    vector<vector<ll>> adj(n);

    ll l = 0, r = 0;
    for (ll i = 0; i < n - m + 1; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            if (st[j] != tar[i + j])
            {
                // i+j → i
                adj[i + j].push_back(i);
            }
            else
            {
                --deg[i] != 0 ?: q[r++] = i;
            }
        }
    }

    vector<bool> vis(n, false);
    ll size = 0;
    while (l < r)
    {
        ll cur = q[l++]; // cover cur to cur + m - 1
        path.push_back(cur);
        for (ll i = 0; i < m; i++)
        {
            if (!vis[cur + i])
            {
                vis[cur + i] = true;
                for (ll next : adj[cur + i])
                {
                    --deg[next] != 0 ?: q[r++] = next;
                }
            }
        }
    }

    vector<ll> ans;
    for (ll i = n - m; i >= 0; i--)
    {
        ans.push_back(path[i]);
    }
    return ans;
}
