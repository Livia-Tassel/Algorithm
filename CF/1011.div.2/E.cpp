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

bool check(ll k, ll n, vl &a, map<ll, ll> &freq_b)
{
    if (k == 0)
        return false;
    map<ll, ll> freq_c;
    for (ll i = 0; i < n; i++)
    {
        freq_c[a[i] % k]++;
    }
    return freq_c == freq_b;
}

void solve()
{
    ll n;
    cin >> n;
    vl a(n), b(n), as(n), bs(n);

    ll s_a = 0, b_max = 0;
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        as[i] = a[i];
        s_a += a[i];
    }

    ll s_b = 0;
    bool all = true;
    map<ll, ll> freq_b;
    for (ll i = 0; i < n; i++)
    {
        cin >> b[i];
        bs[i] = b[i];
        s_b += b[i];
        freq_b[b[i]]++;
        if (b[i] != 0)
            all = false;
        b_max = max(b_max, b[i]);
    }

    sort(as.begin(), as.end());
    sort(bs.begin(), bs.end());
    if (as == bs)
    {
        // large k
        cout << b_max + 1 << "\n";
        return;
    }

    if (all)
    {
        // k = 1
        cout << 1 << "\n";
        return;
    }

    for (ll i = 0; i < n; i++)
    {
        if (as[i] < bs[i])
        {
            cout << -1 << "\n";
            return;
        }
    }

    ll diff = s_a - s_b;
    if (diff == 0)
    {
        cout << -1 << "\n";
        return;
    }

    vl pk;
    for (ll i = 1; i * i <= diff; i++)
    {
        if (diff % i == 0)
        {
            pk.push_back(i);
            if (i * i != diff)
            {
                pk.push_back(diff / i);
            }
        }
    }
    sort(pk.begin(), pk.end());

    // k must be a factor of diff
    // the maximum number of divisors within the range of 1e9 is 1344 and 1e10 is 6912
    for (ll k : pk)
    {
        if (k <= b_max)
            continue;

        if (check(k, n, a, freq_b))
        {
            cout << k << "\n";
            return;
        }
    }

    cout << -1 << "\n";
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