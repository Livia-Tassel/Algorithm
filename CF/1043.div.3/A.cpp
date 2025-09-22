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

void solve(ll m, string a, string b, string c)
{
    string ans = a;
    for (ll i = 0; i < m; i++)
    {
        if (c[i] == 'V')
        {
            ans = b[i] + ans;
        }
        else
        {
            ans += b[i];
        }
    }
    cout << ans << endl;
}
signed main()
{
    ll t, n, m;
    string a, b, c;
    cin >> t;
    while (t--)
    {
        cin >> n >> a >> m >> b >> c;
        solve(m, a, b, c);
    }
}