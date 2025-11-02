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
    vl p(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    ll l = 0, r = n - 1;
    while (r - l > 1)
    {
        if (p[l] > p[l + 1] && p[l] > p[r])
        {
            if (p[l + 1] < p[r])
            {
                cout << "LLR";
            }
            else
            {
                cout << "LRL";
            }
        }
        else if (p[l] > p[l + 1] && p[l] < p[r])
        {
            cout << "LLR";
        }
        else if (p[l] < p[l + 1] && p[l] > p[r])
        {
            cout << "LRL";
        }
        else
        {
            cout << "RLL";
        }
        l += 2;
        r -= 1;
    }

    if (r >= l)
    {
        for (ll i = 0; i <= (r - l); i++)
        {
            cout << "L";
        }
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