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
const ll maxl = 63;

void solve()
{
    ll u, v, w;
    cin >> u >> v >> w;
    ll a = 0, b = 0, c = 0;
    bool ans = true;
    for (ll l = maxl - 1; l >= 0; l--)
    {
        ll bit_u = u >> l & 1, bit_v = v >> l & 1, bit_w = w >> l & 1;
        bool found = false;
        for (ll bit_a : {0, 1})
        {
            for (ll bit_b : {0, 1})
            {
                for (ll bit_c : {0, 1})
                {
                    if ((bit_a & bit_b) == bit_u &&
                        (bit_b & bit_c) == bit_v &&
                        (bit_a & bit_c) == bit_w)
                    {
                        found = true;
                        a |= bit_a << l;
                        b |= bit_b << l;
                        c |= bit_c << l;
                        break;
                    }
                }
                if (found)
                {
                    break;
                }
            }
            if (found)
            {
                break;
            }
        }
        if (!found)
        {
            ans = false;
            break;
        }
    }
    if (!ans)
    {
        cout << "NO\n";
    }
    else
    {
        cout << "YES\n";
    }
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