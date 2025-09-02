#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;
using ll = long long;
using vb = vector<bool>;
using vl = vector<ll>;

ll cycles(ll n, vl &p)
{
    vb vis(n + 1, false);
    ll cl = 0;
    for (ll i = 1; i < n + 1; ++i)
    {
        if (!vis[i])
        {
            cl++;
            ll cur = i;
            while (!vis[cur])
            {
                vis[cur] = true;
                cur = p[cur - 1];
            }
        }
    }
    return cl;
}