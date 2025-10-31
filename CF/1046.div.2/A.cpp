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
bool check(ll a, ll b)
{
    return !(a - 2 * b > 2);
}
void solve()
{
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    if (c < a || d < b)
    {
        cout << "NO" << endl;
        return;
    }

    if (check(max(a, b), min(a, b)) && check(max(c - a, d - b), min(c - a, d - b)))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
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