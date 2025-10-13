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
    cin >> n;
    if (n % 2 == 0)
    {
        cout << -1 << endl;
        return;
    }

    for (ll i = 1; i <= n; i += 2)
    {
        cout << i << " ";
    }
    for (ll i = 2; i <= n; i += 2)
    {
        cout << i << " ";
    }
    cout << endl;
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