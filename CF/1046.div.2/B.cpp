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
    ll n, k, p = 1;
    cin >> n >> k;
    string s;
    cin >> s;

    vl ans(n);
    for (ll i = 0, seq = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            ans[i] = p++;
            seq++;
            if (seq >= k)
            {
                cout << "NO" << endl;
                return;
            }
        }
        else
        {
            seq = 0;
        }
    }
    for (ll i = 0; i < n; i++)
    {
        if (s[i] == '0')
        {
            ans[i] = p++;
        }
    }
    cout << "YES" << endl;
    for (ll i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
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