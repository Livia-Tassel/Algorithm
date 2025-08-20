#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stack>
#include <queue>
#include <list>
#include <map>
#define ll long long
using namespace std;
const ll MAXN = 5001;
const ll MAXM = 5e5 + 1;
const ll mod = 80112002;

ll head[MAXN], nexe[MAXM], to[MAXM];
ll q[MAXN], deg[MAXN], lines[MAXN];
ll cnt;

void add_edge(ll u, ll v)
{
    nexe[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

vector<vector<ll>> adj;
void build()
{
    cnt = 1;
    memset(head, 0, sizeof(head));
    memset(deg, 0, sizeof(deg));
    memset(lines, 0, sizeof(lines));

    for (vector<ll> &e : adj)
    {
        ll u = e[0], v = e[1];
        add_edge(u, v);
        deg[v]++;
    }
}
// count the number of food chains of a food web
ll prey(ll n, ll m)
{
    build();
    ll l = 0, r = 0;
    for (ll i = 1; i < n + 1; i++)
    {
        if (deg[i] != 0)
        {
        }
        else
        {
            q[r++] = i, lines[i] = 1;
        }
    }

    ll ans = 0;
    while (l < r)
    {
        ll u = q[l++];
        if (head[u] != 0)
        {
            for (ll eid = head[u]; eid != 0; eid = nexe[eid])
            {
                ll v = to[eid];
                --deg[v] != 0 ?: q[r++] = v;
                lines[v] = (lines[v] + lines[u]) % mod;
            }
        }
        else
        {
            ans = (ans + lines[u]) % mod;
        }
    }

    return ans;
}

// n employees, each with a single favorite employee， an employee will only attend a meeting if they are seated next to their favorite, return the maximum number of employees who can attend.
ll max_vit(vector<ll> &favor)
{
    ll n = favor.size();
    vector<ll> deg(n, 0);
    for (ll i = 0; i < n; i++)
    {
        deg[favor[i]]++;
    }

    ll q[n];
    ll l = 0, r = 0;
    for (ll i = 0; i < n; i++)
    {
        deg[i] != 0 ?: q[r++] = i;
    }

    vector<ll> dp(n, 0);
    while (l < r)
    {
        ll cur = q[l++], next = favor[cur];
        dp[next] = max(dp[next], dp[cur] + 1);
        --deg[next] != 0 ?: q[r++] = next;
    }

    // only the nodes on the cycles remain.
    ll sum_of_smallring = 0;
    ll sum_big = 0;
    for (ll i = 0; i < n; i++)
    {
        if (deg[i] > 0)
        {
            ll ring_size = 1;
            deg[i] = 0;
            for (ll j = favor[i]; i != j; j = favor[j])
            {
                ring_size++;
                deg[j] = 0;
            }

            if (ring_size > 2)
            {
                sum_big = max(sum_big, ring_size);
            }
            else
            {
                sum_of_smallring += (2 + dp[i] + dp[favor[i]]);
            }
        }
    }

    return max(sum_of_smallring, sum_big);
}

signed main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    ll n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        ll u, v;
        cin >> u >> v;
        adj.push_back({u, v});
    }

    cout << prey(n, m);
    return 0;
}