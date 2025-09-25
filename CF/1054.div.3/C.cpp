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
const ll maxn = 2e5 + 5;
vl a(maxn);
ll solve(ll n, ll k)
{
    ll cnt = 0;
    vl vis(n + 1, 0);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] == k)
            cnt++;
        if (a[i] < k)
            vis[a[i]]++;
    }
    ll ans = cnt, sml = 0;
    for (ll i = 0; i < k; i++)
    {
        if (!vis[i])
            sml++;
    }
    if (cnt > sml)
        return ans;
    else
        return ans + (sml - cnt);
}
signed main()
{
    ll t, n, k;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        cout << solve(n, k) << endl;
    }
}
