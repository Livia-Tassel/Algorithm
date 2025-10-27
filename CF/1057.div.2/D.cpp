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
using namespace std;
using ll = long long;
using vl = vector<ll>;
const ll inf = (1LL << 60);

ll cto(ll x, ll y)
{
    return llabs(x - y);
}

ll ctr(ll x, ll y, ll z)
{
    // cost to make all three equal = sum abs to median
    ll arr[3] = {x, y, z};
    sort(arr, arr + 3);
    ll m = arr[1];
    return llabs(x - m) + llabs(y - m) + llabs(z - m);
}

ll f(const vl &b)
{
    ll n = b.size();
    if (n == 0)
        return 0;
    if (n == 1)
        return 0;

    vl dp(n, inf);
    // dp[i] = min cost to cover 0..i
    for (ll i = 0; i < n; ++i)
    {
        // cover last two: i-1, i
        if (i - 1 >= 0)
        {
            // i = 1, base = 0
            ll base = (i - 2 >= 0 ? dp[i - 2] : (i - 2 == -1 ? 0 : inf));
            if (base < inf)
            {
                dp[i] = min(dp[i], base + cto(b[i - 1], b[i]));
            }
        }
        // cover last three: i-2, i-1, i
        if (i - 2 >= 0)
        {
            ll base = (i - 3 >= 0 ? dp[i - 3] : (i - 3 == -1 ? 0 : inf));
            if (base < inf)
            {
                dp[i] = min(dp[i], base + ctr(b[i - 2], b[i - 1], b[i]));
            }
        }
    }
    return dp[n - 1];
}

void solve()
{
    ll n;
    cin >> n;
    vl a(n);
    for (ll i = 0; i < n; ++i)
        cin >> a[i];

    // all equal -> 0
    bool all_equal = true;
    for (ll i = 1; i < n; ++i)
    {
        if (a[i] != a[0])
        {
            all_equal = false;
            break;
        }
    }
    if (all_equal)
    {
        cout << 0 << '\n';
        return;
    }

    // try starts {0, n-1, n-2} (unique, valid)
    vl s;
    s.push_back(0);
    if (n - 1 != 0)
        s.push_back(n - 1);
    if (n - 2 >= 0 && n - 2 != 0 && n - 2 != n - 1)
        s.push_back(n - 2);

    ll ans = inf;
    for (ll ss : s)
    {
        vl b(n);
        for (ll i = 0; i < n; ++i)
            b[i] = a[(ss + i) % n];
        ans = min(ans, f(b));
    }
    cout << ans << '\n';
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
    return 0;
}