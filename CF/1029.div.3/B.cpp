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

void solve()
{
    ll n, mid;
    cin >> n;
    vl arr(n);
    mid = (n % 2 ? n / 2 : (n + 1) / 2);

    arr[mid - 1] = n - 1, arr[mid] = n;
    for (ll l = mid - 2; l >= 0; l--)
    {
        arr[l] = arr[l + 1] - 2;
    }
    for (ll r = mid + 1; r < n; r++)
    {
        arr[r] = arr[r - 1] - 2;
    }
    for (ll i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}