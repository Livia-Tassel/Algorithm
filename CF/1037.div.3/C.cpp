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

bool solve(ll n, ll k)
{
    ll h, nh, init, g = 1;
    set<ll> s;

    for (ll i = 1; i <= n; i++)
    {
        cin >> h;
        if (k == i)
            init = h;

        s.insert(h);
    }
    auto it = s.find(init);
    h = *it;
    while (++it != s.end())
    {
        nh = *(it);
        // cout << "h: " << h << ",nh: " << nh << ",g: " << g << endl;
        if (nh - h + g - 1 > h)
            return false;

        g += (nh - h);
        h = nh;
    }

    return true;
}
signed main()
{
    ll t, n, k;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        cout << (solve(n, k) ? "YES" : "NO") << endl;
    }
}