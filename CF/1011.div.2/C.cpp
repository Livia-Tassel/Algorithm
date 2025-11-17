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
    ll x, y;
    cin >> x >> y;
    // a + b = a ^ b
    if (x == y)
    {
        cout << -1 << endl;
        return;
    }
    // k = 2^n - max(x, y)
    // (x + k) + (y + k) = 2^(n+1) - (x - y), x > y
    // (x + k) ^ (y + k) = 2^n ^ (2^n - (x -y)) = 2^(n+1) - (x - y)
    ll pt = 1LL << 30;
    cout << pt - max(x, y) << endl;
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