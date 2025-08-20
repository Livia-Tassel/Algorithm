#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using ll = long long;
const ll MAXN = 5001, MAX_EDGES = 200001;
using namespace std;
ll n, m;

void prim()
{
    vector<vector<pair<ll, ll>>> graph(n + 1);

    for (ll i = 0; i < m; ++i)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    priority_queue<
        pair<ll, ll>,
        vector<pair<ll, ll>>,
        greater<pair<ll, ll>>>
        pq;

    vector<bool> vis(n + 1, false);

    ll cnt = 1;
    vis[1] = true;
    ll ans = 0;

    for (const auto &edge : graph[1])
    {
        ll v = edge.first;
        ll w = edge.second;
        pq.push({w, v});
    }

    while (!pq.empty())
    {
        pair<ll, ll> edge = pq.top();
        pq.pop();

        ll cost = edge.first;
        ll next = edge.second;

        if (!vis[next])
        {
            cnt++;
            vis[next] = true;
            ans += cost;

            for (const auto &ne : graph[next])
            {
                ll v = ne.first;
                ll w = ne.second;
                pq.push({w, v});
            }
        }
    }

    if (cnt != n)
    {
        cout << "orz";
    }
    else
    {
        cout << ans;
    }
    cout << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    prim();
    return 0;
}