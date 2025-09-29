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

vb comp(1e5 + 1);
vl prim;
void sieve()
{
    for (ll i = 2; i * i <= 1e5; i++)
        if (!comp[i])
            for (ll j = i * i; j <= 1e5; j += i)
                comp[j] = true;
    for (ll i = 2; i <= 1e5; i++)
        if (!comp[i])
            prim.push_back(i);
}

void solve()
{
    ll n, cnt;
    cin >> n;
    vl p(n + 1);
    for (auto it = prim.rbegin(); it != prim.rend(); ++it)
    {
        vl cycle;
        cnt = 0;
        // n = 10
        // i = 7 => cycle = {7}
        // i = 5 => cycle = {5, 10}
        // i = 3 => cycle = {3, 6, 9}
        // i = 2 => cycle = {2, 4, 8}
        for (ll i = *it; i <= n; i += *it)
            if (!p[i])
            {
                cycle.push_back(i);
                cnt++;
            }

        // p[7] = 7
        // p[5] = 10, p[10] = 5
        // p[3] = 6, p[6] = 9, p[9] = 3
        // p[2] = 4, p[4] = 6, p[8] = 2
        for (ll i = 0; i < cnt; i++)
            p[cycle[i]] = cycle[(i + 1) % cnt];
    }

    // p[1] = 1,...
    for (ll i = 1; i <= n; i++)
        if (!p[i])
            p[i] = i;
    for (ll i = 1; i <= n; i++)
        cout << p[i] << (i != n ? ' ' : '\n');
}

signed main()
{
    sieve();
    ll t;
    cin >> t;
    while (t--)
        solve();
}