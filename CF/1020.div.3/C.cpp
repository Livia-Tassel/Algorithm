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
    vl a(n), b(n);
    ll min = LLONG_MAX, max = LLONG_MIN;
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        min = std::min(min, a[i]);
        max = std::max(max, a[i]);
    }

    ll sum = -1, flag = 1;
    bool pa = true;
    for (ll i = 0; i < n; i++)
    {
        cin >> b[i];
        if (b[i] != -1)
        {
            flag = 0;
            if (sum == -1)
            {
                sum = a[i] + b[i];
            }
            else
            {
                if (a[i] + b[i] != sum)
                {
                    pa = false;
                }
            }
        }
    }
    if (flag)
    {
        cout << k + min - max + 1 << endl;
    }
    else
    {
        if (pa)
        {
            for (ll i = 0; i < n; i++)
            {
                if (b[i] == -1 && (a[i] > sum || a[i] + k < sum))
                {
                    cout << 0 << endl;
                    return;
                }
            }
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
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