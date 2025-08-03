#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#define ll long long
using namespace std;
const ll MAXN = 501;
ll arr[MAXN], help[MAXN];

// reverse pairs are pairs (i, j) such that i < j and arr[i] > 2 * arr[j]
ll merge_and_count(ll l, ll m, ll r)
{
    ll ans = 0;
    // 2 5 6   1 2 4
    //     i       j
    for (ll j = r, i = m; i >= l; i--)
    {
        while (j >= m + 1 && arr[i] <= 2 * arr[j])
        {
            j--;
        }
        ans += (j - m);
    }

    // merge
    ll pl = l, pr = m + 1, ph = l;
    while (pl <= m && pr <= r)
    {
        if (arr[pl] <= arr[pr])
        {
            help[ph++] = arr[pl++];
        }
        else
        {
            help[ph++] = arr[pr++];
        }
    }
    while (pl <= m)
    {
        help[ph++] = arr[pl++];
    }
    while (pr <= r)
    {
        help[ph++] = arr[pr++];
    }
    for (ll i = l; i <= r; i++)
    {
        arr[i] = help[i];
    }
    return ans;
}

ll reverse_pairs(ll l, ll r)
{
    if (l == r)
    {
        return 0;
    }
    ll mid = (l + r) / 2;
    ll cnt_l, cnt_r, cross_cnt;
    cnt_l = reverse_pairs(l, mid);
    cnt_r = reverse_pairs(mid + 1, r);
    cross_cnt = merge_and_count(l, mid, r);
    return cnt_l + cnt_r + cross_cnt;
}

signed main()
{
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    ll ans = reverse_pairs(0, n - 1);
    cout << ans << endl;
}