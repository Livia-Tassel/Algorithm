#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#define ll long long
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pii = pair<int, int>;

void solve()
{
    ll n;
    cin >> n;
    vl a(n + 1);
    for (ll i = 1; i <= n; ++i)
        cin >> a[i];

    vvi g(n + 1);
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // mx[v] = max pref alternating sum from v to root
    // mn[v] = min pref alternating sum from v to root
    vl mx(n + 1, 0), mn(n + 1, 0);

    mx[1] = mn[1] = a[1];
    stack<pii> st;
    st.push({1, 0});
    // dfs
    while (!st.empty())
    {
        auto cur = st.top();
        st.pop();
        int v = cur.first;
        int p = cur.second;
        for (int to : g[v])
            if (to != p)
            {
                // mx[to] = max(a[to], a[to] - mn[v])
                // mn[to] = min(a[to], a[to] - mx[v])
                mn[to] = min(a[to], a[to] - mx[v]);
                mx[to] = max(a[to], a[to] - mn[v]);

                st.push({to, v});
            }
    }

    for (int i = 1; i <= n; ++i)
    {
        cout << mx[i] << (i == n ? '\n' : ' ');
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
