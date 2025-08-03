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

// consider that:
//    1. whether the answer for a large range can be decomposed into the answer for the left part + the answer for the right part + the answer generated across the left and right parts.
//    2. furthermore, if calculating the answer generated across the left and right parts would be more convenient due to the left and right parts being individually sorted.

ll merge_and_sum(ll l, ll m, ll r)
{
    ll ans = 0;
    // 4 6 7 7   5 6 6 8
    // i         j
    for (ll j = m + 1, i = l, sum = 0; j <= r; j++)
    {
        while (i <= m && arr[i] <= arr[j])
        {
            sum += arr[i];
            i++;
        }
        ans += sum;
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

ll small_sum(ll l, ll r)
{
    if (l == r)
    {
        return 0;
    }
    ll mid = (l + r) / 2;
    ll suml, sumr, sumc;

    suml = small_sum(l, mid);
    sumr = small_sum(mid + 1, r);
    sumc = merge_and_sum(l, mid, r);
    
    return suml + sumr + sumc;
}

signed main()
{
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    ll result = small_sum(0, n - 1);
    cout << "total small sum: " << result << endl;
    return 0;
}
