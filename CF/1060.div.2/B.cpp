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
const ll inf = LLONG_MAX;

ll solve()
{
    ll n;
    cin >> n;
    vl a(n + 2, inf), prmx(n + 1, 0);
    for (ll i = 1; i <= n; i++)
    {
        cin >> a[i];
        prmx[i] = max(prmx[i - 1], a[i]);
    }

    for (ll i = 2; i <= n; i += 2)
    {
        a[i] = prmx[i];
    }
    ll cnt = 0;
    for (ll i = 1; i <= n; i += 2)
    {
        ll lt = min(a[i - 1], a[i + 1]);
        if (a[i] >= lt)
        {
            cnt += (a[i] - lt + 1);
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