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

    vl a(n);
    auto swap = [&](ll x)
    {
        cout << "swap " << x + 1 << endl;
    };
    auto throw_ball = [&](ll x)
    {
        cout << "throw " << x + 1 << endl;
        ll ret;
        cin >> ret;
        return ret;
    };
    auto answer = [&]()
    {
        cout << "!";
        for (auto i : a)
            cout << ' ' << i;
        cout << endl;
    };

    // J(i) = 1 + J(i + a[i])
    // for any k >= n, J(k) = 0
    // a[i] = 1, J[i] = 1 + J(i + 1)
    // a[i] = 2, J[i] = 1 + J(i + 2)

    // 「3n/2」, n throw + n/2 swap
    // if J(i + 1) == J(i + 2), swap(i, i + 1), then throw i + 1
    // if J(i + 2) == J(i + 3), then J(i + 1) == J(i + 2) == J(i + 3), that is impossible
    // so J(i + 2) != J(i + 3), then a[i] can be determined
    vl jumps(n + 2);
    for (ll i = n - 1; i >= 0; i--)
    {
        if (jumps[i + 1] == jumps[i + 2])
        {
            // a[i] = 0
            jumps[i] = jumps[i + 1] + 1;
        }
        else
        {
            jumps[i] = throw_ball(i);
            if (jumps[i] == jumps[i + 1] + 1)
                a[i] = 1;
            else
                a[i] = 2;
        }
    }

    for (ll i = 0; i + 1 < n; i++)
    {
        if (a[i] == 0)
        {
            swap(i);
            ll jumps_i = throw_ball(i + 1);
            // J(i + 1) == J(i + 2), so J(i + 2) != J(i + 3)
            if (jumps_i == jumps[i + 2] + 1)
                a[i] = 1;
            else
                a[i] = 2;
        }
    }

    swap(n - 2);
    ll jumps_last = throw_ball(n - 2);
    if (jumps_last == 2)
        a[n - 1] = 1;
    else
        a[n - 1] = 2;
    answer();
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