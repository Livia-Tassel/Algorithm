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
    ll n, k;
    cin >> n >> k;
    ll cto = k, ctt = n - k;
    if (cto >= ctt)
    {
        for (ll i = 0; i < ctt - 1; i++)
        {
            cout << 1;
        }
        if (ctt > 0)
        {
            cout << 0;
        }
        for (ll i = 0; i < cto - max(ctt - 1, 0LL); i++)
        {
            cout << 1;
        }
        for (ll i = 0; i < ctt - 1; i++)
        {
            cout << 0;
        }
    }
    else
    {
        for (ll i = 0; i < cto - 1; i++)
        {
            cout << 0;
        }
        if (cto > 0)
        {
            cout << 1;
        }
        for (ll i = 0; i < ctt - max(cto - 1, 0LL); i++)
        {
            cout << 0;
        }
        for (ll i = 0; i < cto - 1; i++)
        {
            cout << 1;
        }
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