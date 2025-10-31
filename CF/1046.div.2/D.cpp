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
using vvl = vector<vl>;

void solve()
{
    ll n;
    cin >> n;

    ll mn = LLONG_MAX, mx = -LLONG_MAX;
    for (ll i = 1; i <= n; i++)
    {
        ll x, y;
        cin >> x >> y;
        mn = min(mn, y - x);
        mx = max(mx, x + y);
    }

    // move to the bottom-right corner beyond the original boundary
    // X` = X + 2V, Y` = Y - 2V
    // min(|x - X`| + |y - Y`|) = min((X` - Y`) + (y - x))
    // min(y - x) + X - Y + 4V == res
    // Y - X == mn - res + 4V
    ll res;
    cout << "? R 1000000000" << endl;
    cin >> res;
    cout << "? R 1000000000" << endl;
    cin >> res;
    cout << "? D 1000000000" << endl;
    cin >> res;
    cout << "? D 1000000000" << endl;
    cin >> res;
    ll q = mn - res + 4000000000ll;

    // move to the top-right corner beyond the original boundary
    // X` = X + 2V, Y` = Y + 2V
    // min(|x - X`| + |y - Y`|) = min((X` + Y`) - (x + y))
    // -max(x + y) + X + Y + 4V == res
    // X + Y == res + mx - 4V
    cout << "? U 1000000000" << endl;
    cin >> res;
    cout << "? U 1000000000" << endl;
    cin >> res;
    cout << "? U 1000000000" << endl;
    cin >> res;
    cout << "? U 1000000000" << endl;
    cin >> res;
    ll p = mx + res - 4000000000ll;

    cout << "! " << (p - q) / 2 << ' ' << (p + q) / 2 << endl;
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