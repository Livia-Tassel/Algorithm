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
using vp = vector<pair<ll, ll>>;

void solve()
{
    ll n, cnt = 0;
    cin >> n;
    vl a(n);
    bool none = true, all = true;
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] != 0)
        {
            all = false;
        }
        else
        {
            cnt++;
            none = false;
        }
    }

    if (none)
    {
        cout << 1 << endl;
        cout << 1 << " " << n << endl;
        return;
    }
    if (all || cnt == n - 1)
    {
        cout << 3 << endl;
        cout << n - 1 << " " << n << endl;
        cout << 1 << " " << n - 2 << endl;
        cout << 1 << " " << 2 << endl;
        return;
    }

    ll k = 1;
    vp ans;
    for (ll i = n - 1, j; i >= 0; i--)
    {
        j = i;
        while (j >= 0 && a[j] == 0)
        {
            j--;
        }
        if (i != j)
        {
            k++;
            if (j >= 0)
            {
                ans.push_back({j + 1, i + 1});
            }
            else
            {
                ans.push_back({j + 2, i + 2});
            }
            i = j;
        }
    }

    cout << k << endl;
    for (auto &p : ans)
    {
        cout << p.first << " " << p.second << endl;
    }
    cout << 1 << " " << n - cnt << endl;
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