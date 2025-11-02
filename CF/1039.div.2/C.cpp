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
    ll n;
    cin >> n;
    vl b(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    ll mpre = b[0];
    for (ll i = 1; i < n; i++)
    {
        if (b[i] >= 2 * mpre)
        {
            cout << "NO" << endl;
            return;
        }
        mpre = min(mpre, b[i]);
    }
    cout << "YES" << endl;
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