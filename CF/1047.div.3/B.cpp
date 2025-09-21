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
const ll maxn = 200005;

vl p(maxn);
ll solve(ll n)
{
    ll g = n + 1;
    for (ll i = 1; i <= n; i++)
    {
        cout << g - p[i] << " ";
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
        for (ll i = 1; i <= n; i++)
        {
            cin >> p[i];
        }
        solve(n);
    }
}