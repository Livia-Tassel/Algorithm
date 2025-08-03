#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#define ll long long
using namespace std;
ll arr[1000001];

ll f(ll l, ll r)
{
    if (l == r)
    {
        return arr[l];
    }
    ll mid = (l + r) / 2;

    // master: T(N) = a * T(N/b) + O(N^c), sub-processes must be of equal scale
    // log(b a) > c, then T(N) = O(N^log(b a))
    // log(b a) < c, then T(N) = O(N^c)
    // log(b a) = c, then T(N) = O(N^c * log N)
    // where a = 2, b = 2, c = 0
    // T(N) = 2 * T(N/2) + O(1)
    // T(N) = O(N^log(2 2)) = O(N^1) = O(N)

    // especially, T(N) = 2 * T(N/2) + O(N * log N)
    // T(N) = O(N * (log N)^2)

    ll lmax = f(l, mid);
    ll rmax = f(mid + 1, r);
    return max(lmax, rmax);
}

signed main()
{
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    ll ans = f(0, n - 1);
    cout << ans << endl;
    return 0;
}