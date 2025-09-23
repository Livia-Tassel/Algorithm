#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using vi = vector<int>;
using vvi = vector<vector<int>>;
using namespace std;

void solve()
{
    int n;
    cin >> n;

    // n=1, d=0; n=2, d=1; n=3, d=2
    if (n <= 3)
    {
        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;
            cin >> u >> v;
        }

        cout << 0 << endl;
        return;
    }

    vvi g(n);
    vi deg(n, 0);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    int lf = 0;
    for (int i = 0; i < n; ++i)
    {
        if (deg[i] == 1)
        {
            lf++;
        }
    }

    int mx = 0;
    for (int i = 0; i < n; ++i)
    {
        int lfn = 0;
        for (int ng : g[i])
        {
            if (deg[ng] == 1)
            {
                lfn++;
            }
        }
        mx = max(mx, lfn);
    }

    cout << lf - mx << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}