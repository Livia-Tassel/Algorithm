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

void solve(ll n)
{
    for (ll i = 1; i <= n; i++)
    {
        if (i % 2)
            cout << -1 << " ";
        else if (i < n)
            cout << 3 << " ";
        else
            cout << 2 << " ";
    }
    cout << endl;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        solve(n);
    }
}