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

vl ans(1000001);
void solve(ll n)
{
    ll base = 11, cnt = 0;
    while (base <= n)
    {
        if (n % base == 0)
        {
            ans[cnt++] = n / base;
        }
        base = 10 * base - 9;
    }
    cout << cnt << endl;
    if (cnt)
    {
        sort(ans.begin(), ans.begin() + cnt);
        for (ll i = 0; i < cnt; i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
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