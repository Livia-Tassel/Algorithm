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
using vp = vector<pair<ll, ll>>;
const ll maxn = 6e3 + 5;
ll root[maxn];
ll n;

void init()
{
    for (ll i = 1; i <= 2 * n; i++)
    {
        root[i] = i;
    }
}

ll find(ll x)
{
    return root[x] != x ? root[x] = find(root[x]) : x;
}

void un(ll x, ll y)
{
    ll fx = find(x), fy = find(y);
    if (fx != fy)
    {
        root[fy] = fx;
    }
}

void solve()
{
    cin >> n;
    init();
    vl a(n), b(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i] >> b[i];
    }

    vl ans;
    ll cnt = 0;
    for (ll i = 0; i < n; i++)
    {
        if (find(a[i]) != find(b[i]))
        {
            un(a[i], b[i]);
            ans.push_back(i + 1);
            cnt++;
        }
    }
    cout << cnt << endl;
    for (ll i = 0; i < cnt; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
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