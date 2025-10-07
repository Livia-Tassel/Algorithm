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
    ll n, ans = 1;
    cin >> n;
    vl arr(n);
    for (ll i = 0; i < n; i++)
        cin >> arr[i];

    set<ll> seg, next;
    seg.insert(arr[0]);
    next.insert(arr[0]);
    for (ll i = 1; i < n; i++)
    {
        next.insert(arr[i]);
        if (seg.count(arr[i]))
        {
            seg.erase(arr[i]);
            if (seg.empty())
            {
                ans++;
                seg = next;
            }
        }
    }
    cout << ans << endl;
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