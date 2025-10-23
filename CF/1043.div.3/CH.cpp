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

void solve(ll n, ll k)
{
    if (k >= n)
    {
        cout << 3 * n << endl;
        return;
    }

    vl tri(101, 0);
    auto it = upper_bound(menl.begin(), menl.begin() + cnt, n);
    ll dex = it - menl.begin() - 1;

    ll cost = 0, ct = 0;
    while (n > 0 && ct <= k)
    {
        ll tims = n / menl[dex];
        ct += tims;
        tri[dex] = tims;
        cost += tims * coins[dex];
        n %= menl[dex];

        it = upper_bound(menl.begin(), menl.begin() + cnt, n);
        dex = it - menl.begin() - 1;
    }
    if (ct <= k)
    {
        k -= ct;
        for (ll i = 100, disp; i >= 1, k >= 2; i--)
        {
            if (tri[i] != 0)
            {
                disp = min(k / 2, tri[i]);
                k -= 2 * disp;
                tri[i - 1] += 3 * disp;
                cost -= disp * (coins[i] - 3 * coins[i - 1]);
            }
        }
        cout << cost << endl;
    }
    else
        cout << -1 << endl;
}
signed main()
{
    ll t, n, k;
    cin >> t;
    build();
    while (t--)
    {
        cin >> n >> k;
        solve(n, k);
    }
}