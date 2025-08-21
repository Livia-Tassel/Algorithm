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
const ll MAXN = 5001, MAXM = 200001;

// undirected weighted graph
ll root[MAXN];
ll n, m;

void init()
{
    for (ll i = 1; i < n + 1; i++)
    {
        root[i] = i;
    }
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

vector<vector<ll>> adj(MAXM, vector<ll>(3));
// O (m * log m + n + m)
void kruskal()
{
    init();
    for (ll i = 0; i < m; i++)
    {
        cin >> adj[i][0] >> adj[i][1] >> adj[i][2];
    }
    sort(adj.begin(), adj.begin() + m, [](const vector<ll> &a, const vector<ll> &b)
         { return a[2] < b[2]; });

    ll ans = 0, cnt = 0;
    for (ll i = 0; i < m; i++)
    {
        vector<ll> &edge = adj[i];
        ll u = edge[0], v = edge[1], w = edge[2];
        if (un(u, v))
        {
            cnt++, ans += w;
        }
    }

    if (cnt != n - 1)
    {
        cout << "orz";
    }
    else
    {
        cout << ans;
    }
}

signed main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    cin >> n >> m;
    kruskal();

    return 0;
}