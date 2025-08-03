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

void merge(ll l, ll m, ll r)
{
    ll pl = l, pr = m + 1, ph = l;
    while (pl <= m && pr <= r)
    {
        if (arr[pl] < arr[pr])
        {
            help[ph] = arr[pl];
            ph++;
            pl++;
        }
        else
        {
            help[ph] = arr[pr];
            ph++;
            pr++;
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
}

// form top to bottom
// T(n) = 2 * T(n/2) + O(n)
// time O(n * log n)
// space O(n)
void mergesort(ll l, ll r)
{
    if (l == r)
    {
        return;
    }
    ll mid = (l + r) / 2;
    mergesort(l, mid);
    mergesort(mid + 1, r);
    merge(l, mid, r);
}

// form bottom to top
void mergesort(ll n)
{
    ll l, m, r;
    for (ll step = 1; step < n; step <<= 1)
    {
        l = 0;
        while (l < n)
        {
            m = l + step - 1;
            if (m + 1 >= n)
            {
                break;
            }
            r = min(l + (step << 1) - 1, n - 1);
            merge(l, m, r);
            l = r + 1;
        }
    }
}

signed main()
{
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    // mergesort(0, n - 1);
    // for (ll i = 0; i < n; i++)
    // {
    //     cout << arr[i] << " ";
    // }
    // cout << endl;
    mergesort(n);
    for (ll i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
