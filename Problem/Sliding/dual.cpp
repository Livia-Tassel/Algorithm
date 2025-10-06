#include <iostream>
#include <vector>
#include <numeric>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;
using ll = long long;
using vl = vector<ll>;

multiset<ll> sml, big;
ll ss = 0, sb = 0;
void add(ll val)
{
    if (!sml.empty() && val <= *sml.rbegin())
    {
        sml.insert(val);
        ss += val;
    }
    else
    {
        big.insert(val);
        sb += val;
    }
}

void remove(ll val)
{
    auto it_big = big.find(val);
    if (it_big != big.end())
    {
        big.erase(it_big);
        sb -= val;
    }
    else
    {
        auto it_sml = sml.find(val);
        if (it_sml != sml.end())
        {
            sml.erase(it_sml);
            ss -= val;
        }
    }
}

void rebalance()
{
    while (sml.size() > big.size() + 1)
    {
        ll val = *sml.rbegin();
        sml.erase(prev(sml.end()));
        big.insert(val);
        ss -= val;
        sb += val;
    }
    while (sml.size() < big.size())
    {
        ll val = *big.begin();
        big.erase(big.begin());
        sml.insert(val);
        sb -= val;
        ss += val;
    }
}

ll get_cost()
{
    if (sml.empty() && big.empty())
        return 0;

    ll median = *sml.rbegin();
    return (median * (ll)sml.size() - ss) + (sb - median * (ll)big.size());
}

void solve()
{
    int n;
    ll k;
    cin >> n >> k;
    vl b(n);
    for (int i = 0; i < n; ++i)
    {
        ll val;
        cin >> val;
        // a[l..r], a[i] - a[l] = i - l, then a[i] - i = a[l] - l
        b[i] = val - (i + 1);
    }

    sml.clear();
    big.clear();
    ss = 0, sb = 0;

    int l = 0, ans = 0;
    for (int r = 0; r < n; ++r)
    {
        add(b[r]);
        rebalance();

        while (get_cost() > k)
        {
            remove(b[l]);
            rebalance();
            l++;
        }

        ans = max(ans, r - l + 1);
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}