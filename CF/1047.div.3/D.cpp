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
const ll maxn = 200005;

vl b(maxn);
unordered_map<ll, pair<ll, vl>> mp;
void solve(ll n)
{
    ll tp = 1;
    vl a(n + 1);

    for (auto &p : mp)
    {
        vl &vp = p.second.second;
        for (ll i = 0; i < p.second.first;)
        {
            for (ll j = 0; j < p.first; j++, i++)
            {
                a[vp[i]] = tp;
            }
            tp++;
        }
    }
    for (ll i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (ll i = 1; i <= n; i++)
        {
            cin >> b[i];

            mp[b[i]].first++;
            // cout << "mp " << mp[b[i]].first << endl;

            mp[b[i]].second.push_back(i);
        }
        bool flag = true;
        for (auto &p : mp)
        {
            // cout << "    " << p.second.first << " " << p.first << endl;
            if (p.second.first % p.first != 0)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            solve(n);
        }
        else
        {
            cout << -1 << endl;
        }
        mp.clear();
    }
}