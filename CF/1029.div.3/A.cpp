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
    ll n, x;
    cin >> n >> x;
    ll l = -1, r = -1;
    for (ll i = 0, dr; i < n; i++)
    {
        cin >> dr;
        if (dr)
            l != -1 ? r = i : l = i;
    }
    if (r - l + 1 <= x)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
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