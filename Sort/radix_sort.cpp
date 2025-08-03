#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define ll long long
using namespace std;
const ll MAXN = 1e6 + 5;
ll arr[MAXN], BASE = 10;

// bits represent the bit-number of the maximum number (BASE-BITS)
void radix_sort(ll n, ll bits)
{
    vector<ll> cnt(BASE, 0);
    for (ll offset = 1; bits > 0; offset *= BASE, bits--)
    {
        memset(cnt.data(), 0, cnt.size() * sizeof(ll));
        for (ll i = 0; i < n; i++)
        {
            ll digit = (arr[i] / offset) % BASE;
            cnt[digit]++;
        }
        for (ll i = 1; i < BASE; i++)
        {
            cnt[i] += cnt[i - 1];
        }

        vector<ll> output(n);
        for (ll i = n - 1; i >= 0; i--)
        {
            ll digit = (arr[i] / offset) % BASE;
            output[--cnt[digit]] = arr[i];
        }

        for (ll i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }
    }
}
signed main()
{
    ll n, bits;
    cin >> n >> bits;
    for (ll i = 0; i < n; i++)
    {
        // (-3 -6 3 6  9) - (-6)
        //   3  0 9 12 15
        cin >> arr[i];
    }
    radix_sort(n, bits);
    for (ll i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}