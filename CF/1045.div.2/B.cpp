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
    vl a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    if (k % 2 == 1)
    {
        for (ll aa : a)
        {
            if (aa % 2 == 1)
            {
                cout << aa + k << " ";
            }
            else
            {
                cout << aa << " ";
            }
        }
        cout << endl;
    }
    else
    {
        for (ll aa : a)
        {
            cout << (k + 1) * aa << " ";
        }
        cout << endl;
    }
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