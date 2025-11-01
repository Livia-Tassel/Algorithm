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

void solve()
{
    ll n;
    bool flag = false;
    cin >> n;
    vl vis(101, 0);
    for (ll i = 0, a; i < n; i++)
    {
        cin >> a;
        if (vis[a])
        {
            flag = true;
        }
        vis[a] = 1;
    }
    cout << (flag ? "YES" : "NO") << endl;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}