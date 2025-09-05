#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#define ll long long
using namespace std;
const ll MAXN = 10001;
ll arr[MAXN];
ll bound_l, bound_r;

ll partition(ll l, ll r, ll x)
{
    ll s = l, p = l;
    ll mid = 0, base = arr[x];
    while (p <= r)
    {
        // 4 3 5 8 7 2 6   base = 4
        //     s     p
        if (arr[p] <= base)
        {
            swap(arr[s], arr[p]);
            if (arr[s] == base)
            {
                mid = s;
            }
            s++;
        }
        p++;
    }
    swap(arr[s - 1], arr[mid]);
    return s - 1;
}

void block_partition(ll l, ll r, ll x)
{
    ll s = l, b = r, p = l;
    ll mid = 0, base = arr[x];
    while (p <= b)
    {
        // 3 5 2 1 5 7 5 8 4
        //   s p     p     b
        if (arr[p] < base)
        {
            swap(arr[s], arr[p]);
            s++, p++;
        }
        else if (arr[p] == base)
        {
            p++;
        }
        else
        {
            swap(arr[p], arr[b]);
            b--;
        }
    }
    bound_l = s - 1;
    bound_r = b + 1;
}

// classic randomized quicksort
// O(n log n) on average, O(n^2) on worst case
void randomized_quicksort(ll l, ll r)
{
    if (l >= r)
    {
        return;
    }
    // rand from l to r
    ll x = l + rand() % (r - l + 1);
    ll mid = partition(l, r, x);
    randomized_quicksort(l, mid - 1);
    randomized_quicksort(mid + 1, r);
}

// blocked randomized quicksort
// O(n log n) on average, O(n^2) on worst case
void randomized_blocked_quicksort(ll l, ll r)
{
    if (l >= r)
    {
        return;
    }
    ll x = l + rand() % (r - l + 1);
    block_partition(l, r, x);

    ll left = bound_l, right = bound_r;
    randomized_blocked_quicksort(l, left);
    randomized_blocked_quicksort(right, r);
}

signed main()
{
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    // randomized_quicksort(0, n - 1);
    randomized_blocked_quicksort(0, n - 1);
    for (ll i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}