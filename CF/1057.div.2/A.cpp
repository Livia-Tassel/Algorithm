#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <numeric>
#include <unordered_map>
#define ll long long
using namespace std;
using vl = vector<ll>;

ll solve()
{
    ll n, cnt = 0;
    cin >> n;
    vl vis(n + 1, 0);
    for (ll i = 0, b; i < n; i++)
    {
        cin >> b;
        if (!vis[b])
        {
            cnt++;
            vis[b] = 1;
        }
    }
    cout << cnt << endl;
}
signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}