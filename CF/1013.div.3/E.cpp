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
const ll maxn = 1e7 + 5;

vl p, prime(maxn, 0);
void ehrlich()
{
    for (ll i = 2; i * i <= maxn; i++)
    {
        if (!prime[i])
        {
            // p.push_back(i);
            for (ll j = i * i; j <= maxn; j += i)
            {
                prime[j] = true;
            }
        }
    }
    for (ll i = 2; i <= maxn; ++i)
    {
        if (!prime[i])
            p.push_back(i);
    }
}
void solve()
{
    ll n;
    cin >> n;
    ll ans = 0;
    // lcm(a, b) / gcd(a, b) == (a * b) / (gcd(a, b) * gcd(a, b))
    // (a / gcd(a, b)) * (b / gcd(a, b)) is prime
    // due to a < b, then a / gcd(a, b) == 1, (b / gcd(a, b)) is prime
    // a = gcd(a, b), b / a is prime
    // for all prime in [2, 1e7], b == a * p <= n
    // ans += n / p, for all p in [2, 1e7]
    for (ll pp : p)
    {
        if (pp > n)
            break;
        ans += n / pp;
    }
    cout << ans << endl;
}
signed main()
{
    ehrlich();
    // cerr << p.size() << endl;
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}