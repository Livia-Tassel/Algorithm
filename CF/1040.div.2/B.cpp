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
    ll n, s, sum = 0, ctf = 0, cts = 0, ctt = 0;
    cin >> n >> s;
    vl a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
        a[i] == 0 ? ctf++ : (a[i] == 1 ? cts++ : ctt++);
    }
    if (sum == s)
    {
        cout << -1 << endl;
    }
    else if (sum > s)
    {
        for (ll i = 0; i < n; i++)
        {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    else
    {
        if (s - sum > 1)
        {
            cout << -1 << endl;
        }
        else
        {
            for (ll i = 0; i < cts; i++)
            {
                cout << 1 << " ";
            }
            for (ll i = 0; i < ctt; i++)
            {
                cout << 2 << " ";
            }
            for (ll i = 0; i < ctf; i++)
            {
                cout << 0 << " ";
            }
            cout << endl;
        }
    }
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