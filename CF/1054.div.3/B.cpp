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
ll solve(ll n)
{
    for (ll i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.begin() + n);
    ll ans = 0;
    for (ll i = 0, j = 1; j < n; i += 2, j += 2)
    {
        ans = max(abs(a[j] - a[i]), ans);
    }
    return ans;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << solve(n) << endl;
    }
}
