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
const ll maxn = 1e9;
vl coins, menl;
ll cnt;
ll qpow(ll x, ll n)
{
    if (n < 0)
        return 0;

    ll ans = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ans *= x;
        }
        x *= x;
        n >>= 1;
    }
    return ans;
}
void build()
{
    cnt = 0;
    while (1)
    {
        ll m = qpow(3, cnt);
        ll c = qpow(3, cnt + 1) + cnt * qpow(3, cnt - 1);
        menl.push_back(m);
        coins.push_back(c);
        if (m > maxn)
        {
            break;
        }
        cnt++;
    }
}
void solve(ll n)
{
    auto it = upper_bound(menl.begin(), menl.begin() + cnt, n);
    ll dex = it - menl.begin() - 1;

    ll cost = 0;
    while (n > 0)
    {
        cost += n / menl[dex] * coins[dex];
        n %= menl[dex];
        it = upper_bound(menl.begin(), menl.begin() + cnt, n);
        dex = it - menl.begin() - 1;
    }
    cout << cost << endl;
}
signed main()
{
    ll t, n;
    cin >> t;
    build();
    // for (ll i = 0; i < cnt; i++)
    // {
    //     cout << menl[i] << " " << coins[i] << endl;
    // }
    while (t--)
    {
        cin >> n;
        solve(n);
    }
}