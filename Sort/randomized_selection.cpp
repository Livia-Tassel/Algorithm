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

void partition(ll l, ll r, ll x)
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

// select the k-th smallest element of arr
ll randomized_selection(ll n, ll k)
{
    ll l = 0, r = n - 1, ans = 0;
    while (l <= r)
    {
        ll x = rand() % (r - l + 1) + l;
        partition(l, r, x);
        if (k <= bound_l)
        {
            r = bound_l;
        }
        else if (k >= bound_r)
        {
            l = bound_r;
        }
        else
        {
            // found the k-th smallest element
            ans = arr[k];
            break;
        }
    }
    return ans;
}

signed main()
{
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    ll k = 11; // find the 5-th smallest element
    ll ans = randomized_selection(n, k - 1);
    cout << "the " << k << "-th smallest element is: " << ans << endl;
}