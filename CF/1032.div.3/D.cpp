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

vl a(41), b(41);
bool check(ll i, ll n)
{
    return (((a[i] <= n && b[i] <= n) || (a[i] > n && b[i] > n)) && a[i] > b[i]) ||
           (a[i] > n && b[i] <= n);
}
void solve(ll n)
{
    ll cnt = 0;
    vl op, opa, opb;
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    for (ll i = 1; i <= n; i++)
        cin >> b[i];

    for (ll i = 1; i <= n; i++)
    {
        if (check(i, n))
        {
            op.push_back(i);
            cnt++;
        }
    }
    for (ll i = 0; i < cnt; i++)
    {
        swap(a[op[i]], b[op[i]]);
    }

    for (ll i = 1; i < n; i++)
    {
        for (ll j = 1; j <= n - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                opa.push_back(j);
                cnt++;
            }
        }
    }
    for (ll i = 1; i < n; i++)
    {
        for (ll j = 1; j <= n - i; j++)
        {
            if (b[j] > b[j + 1])
            {
                swap(b[j], b[j + 1]);
                opb.push_back(j);
                cnt++;
            }
        }
    }
    cout << cnt << endl;
    for (ll sp : op)
        cout << 3 << " " << sp << endl;
    for (ll sp : opa)
        cout << 1 << " " << sp << endl;
    for (ll sp : opb)
        cout << 2 << " " << sp << endl;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        solve(n);
    }
}