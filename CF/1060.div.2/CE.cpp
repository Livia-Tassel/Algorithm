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
#include <random>
#define ll long long
using namespace std;
using vl = vector<ll>;
using vvl = vector<vl>;

#define vp(a)              \
    cout << #a << " = ";   \
    for (auto aa : a)      \
        cout << aa << " "; \
    cout << "\n";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

const ll N = 2e5 + 10;
vvl pfac(N + 1);
void solve()
{
    ll n;
    cin >> n;

    vl a(n), b(n);
    for (ll &aa : a)
        cin >> aa;
    for (ll &bb : b)
        cin >> bb;

    ll ans = 2;
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++)
    {
        for (ll f : pfac[a[i]])
        {
            if (cnt[f] > 0)
                ans = 0;
            cnt[f]++;
        }
    }

    for (ll i = 0; i < n; i++)
    {
        for (ll p : pfac[a[i]])
            cnt[p]--;

        for (ll p : pfac[a[i] + 1])
        {
            if (cnt[p] > 0)
                ans = min(ans, 1LL);
        }

        for (ll p : pfac[a[i]])
            cnt[p]++;
    }

    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (ll i = 2; i <= N; i++)
    {
        if (!pfac[i].empty())
            continue;

        for (ll j = i; j <= N; j += i)
            pfac[j].push_back(i);
    }
    // vp(pfac[12]);

    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}