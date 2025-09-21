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
ll qpow(ll x, ll n)
{
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
void solve(ll k, ll x)
{
    cout << x * qpow(2, k) << endl;
}
signed main()
{
    ll t, k, x;
    cin >> t;
    while (t--)
    {
        cin >> k >> x;
        solve(k, x);
    }
}