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

vl a(101);
void solve(ll n, ll s)
{
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    if (s >= a[n])
        cout << s - a[1] << endl;
    else if (s <= a[1])
        cout << a[n] - s << endl;
    else
        cout << min(2 * a[n] - a[1] - s, a[n] + s - 2 * a[1]) << endl;
}
signed main()
{
    ll t, n, s;
    cin >> t;
    while (t--)
    {
        cin >> n >> s;
        solve(n, s);
    }
}