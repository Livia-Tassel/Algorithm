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
    // through the following three operations, perform an equivalent action to cyclically shifting a row to the right by i times.
    // "1 n" "1 i" "i+1 n"
    cout << 2 * n - 1 << endl;
    cout << 1 << " " << 1 << " " << n << endl;
    for (ll i = 1; i < n; i++)
    {
        cout << i + 1 << " " << 1 << " " << i << endl;
        cout << i + 1 << " " << i + 1 << " " << n << endl;
    }
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