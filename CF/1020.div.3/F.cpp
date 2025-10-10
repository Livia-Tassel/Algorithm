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
    string s;
    cin >> s;
    s = "" + s;
    vl top(n + 1, 0), bot(n + 1, 0);
    ll ans = 0;
    for (ll i = 1; i <= n; ++i)
    {
        if (s[i] == '1')
        {
            top[i] = bot[i - 1] + 1;
        }
        else
        {
            // s[i] == '0'
            top[i] = top[i - 1] + (i - 1);
            bot[i] = bot[i - 1] + (n - i);
        }
        ans = max(ans, max(top[i], bot[i]));
    }
    cout << ans << '\n';
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
