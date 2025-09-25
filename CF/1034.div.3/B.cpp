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
const ll maxn = 2e5 + 5;

vl a(maxn);
bool solve(ll n)
{
    ll j, k, kth, max = -1;
    cin >> j >> k;
    for (ll i = 1; i <= n; i++)
    {
        cin >> a[i];
        max = std::max(max, a[i]);
        if (i == j)
            kth = a[i];
    }
    if (kth == max || k >= 2)
        return true;
    else
        return false;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << (solve(n) ? "YES" : "NO") << endl;
    }
}