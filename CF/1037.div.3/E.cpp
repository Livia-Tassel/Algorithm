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
#include <cmath>
#define ll long long
using namespace std;
using vl = vector<ll>;
const ll maxn = 1e5 + 5;

vl p(maxn), s(maxn);
ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}
ll lcm(ll a, ll b)
{
    if (a == 0 || b == 0)
        return 0;
    return a / gcd(a, b) * b;
}
bool solve(ll n)
{
    bool ok = true;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    vl ans(n + 1);
    for (int i = n; i >= 1; i--)
    {
        // a[i] % p[i] == 0, a[i] % s[i] == 0
        // a[i] % lcm(p[i], s[i]) == 0
        ans[i] = lcm(p[i], s[i]);
    }

    if (ans[1] != p[1])
        ok = false;
    if (ans[n] != s[n])
        ok = false;
    for (int i = 2; i <= n; i++)
    {
        // gcd(p[i-1], a[i]) == p[i] <=> gcd(p[i-1]/p[i], a[i]/p[i]) == 1
        // if gcd(p[i - 1], ans[i]) != p[i], then gcd(p[i-1]/p[i], ans[i]/p[i]) > 1 => gcd(p[i-1]/p[i], a[i]/p[i]) > 1
        if (gcd(p[i - 1], ans[i]) != p[i])
        {
            ok = false;
        }
    }
    for (int i = n - 1; i >= 1; i--)
    {
        if (gcd(s[i + 1], ans[i]) != s[i])
        {
            ok = false;
        }
    }

    return ok;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << (solve(n) ? "YES" : "NO") << endl;
    }
}