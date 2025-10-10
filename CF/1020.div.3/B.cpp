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
    ll n, c;
    cin >> n >> c;
    for (ll i = 0; i < c; i++)
        cout << i << " ";
    for (ll i = n - 1; i >= c; i--)
        cout << i << " ";
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