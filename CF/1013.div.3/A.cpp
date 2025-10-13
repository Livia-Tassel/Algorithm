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
    vl vis = {3, 1, 2, 1, 0, 1};
    ll cnt = 8;
    ll n, flag = 1;
    cin >> n;
    for (ll i = 0, d; i < n; i++)
    {
        cin >> d;
        if (d <= 5 && vis[d] != 0)
        {
            vis[d]--;
            cnt--;
            if (cnt == 0)
            {
                flag = 0;
                cout << i + 1 << endl;
            }
        }
    }
    if (flag)
    {
        cout << 0 << endl;
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