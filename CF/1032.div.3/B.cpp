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

void solve(ll n)
{
    string s;
    cin >> s;
    vl cnt(27, 0);
    bool flag = false;
    for (ll i = 1; i < n - 1; i++)
    {
        if (++cnt[s[i] - 'a'] > 1 || s[i] == s[0] || s[i] == s[n - 1])
        {
            flag = true;
            break;
        }
    }
    cout << (flag ? "YES" : "NO") << endl;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        solve(n);
    }
}