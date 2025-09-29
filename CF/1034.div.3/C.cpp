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
void solve(ll n)
{
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    vl prmn(n + 1), sumx(n + 1);
    prmn[1] = a[1], sumx[n] = a[n];
    for (ll i = 2; i <= n; i++)
    {
        prmn[i] = min(prmn[i - 1], a[i]);
    }
    for (ll i = n - 1; i > 0; i--)
    {
        sumx[i] = max(sumx[i + 1], a[i]);
    }
    vl ans(n + 1, 0);
    ans[1] = 1, ans[n] = 1;
    for (ll i = 2; i < n; i++)
    {
        if (prmn[i] == a[i] || sumx[i] == a[i])
        {
            ans[i] = 1;
        }
    }
    for (ll i = 1; i <= n; i++)
        cout << ans[i];
    cout << endl;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        solve(n);
    }
}