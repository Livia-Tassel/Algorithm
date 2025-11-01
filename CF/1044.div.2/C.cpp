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
using vb = vector<bool>;

void solve()
{
    ll n;
    cin >> n;

    vl L(n + 1);
    ll max = 0;
    ll s = -1;

    // "1 2 ... n"
    string all;
    for (ll i = 1; i <= n; ++i)
    {
        all += " " + to_string(i);
    }

    for (ll i = 1; i <= n; ++i)
    {
        // "? i n 1 2 ... n"
        cout << "? " << i << " " << n << all << endl;

        ll len;
        cin >> len;
        L[i] = len;

        // find the longest path
        if (len > max)
        {
            max = len;
            s = i;
        }
    }

    // reconstruct the longest path
    vl path;
    path.push_back(s);

    vb in_path(n + 1, false);
    in_path[s] = true;

    ll tar = max - 1; // v2 -> K-1
    for (ll i = 0; i < max - 1; ++i)
    {
        for (ll u = 1; u <= n; ++u)
        {
            if (in_path[u] || L[u] != tar)
                continue;

            // S = {v1, ..., v(i+1), u}
            ll k = path.size() + 1;

            // "? v1 k v1 ... v(i+1) u"
            cout << "? " << s << " " << k;
            for (ll node : path)
            {
                cout << " " << node;
            }
            cout << " " << u << endl;

            ll res;
            cin >> res;
            if (res == k)
            {
                path.push_back(u);
                in_path[u] = true;
                tar--;
                break;
            }
        }
    }

    cout << "! " << max;
    for (ll node : path)
    {
        cout << " " << node;
    }
    cout << endl;
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