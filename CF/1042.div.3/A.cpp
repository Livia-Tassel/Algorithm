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
const ll maxn = 11;

vl a(maxn), b(maxn);
ll solve(ll n)
{
    ll ans = 0;
    for (ll i = 0; i < n; i++)
        ans += a[i] > b[i] ? a[i] - b[i] : 0;
    return ans + 1;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (ll i = 0; i < n; i++)
            cin >> a[i];
        for (ll i = 0; i < n; i++)
            cin >> b[i];

        cout << solve(n) << endl;
    }
}