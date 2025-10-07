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

bool solve()
{
    ll n;
    cin >> n;
    vl arr(n + 1);
    for (ll i = 1; i <= n; i++)
        cin >> arr[i];

    // ll flag = true;
    // ll ase = arr[n] / n, des = arr[n] % n;
    // for (ll i = 1; i <= n; i++)
    // {
    //     if (arr[i] - ase * i - des * (n - i + 1) != 0)
    //         flag = false;
    // }
    // if (flag)
    //     return true;

    // des = arr[1] / n, ase = arr[1] % n;
    // for (ll i = 1; i <= n; i++)
    // {
    //     if (arr[i] - ase * i - des * (n - i + 1) != 0)
    //         return false;
    // }
    // return true;

    // arr[i] - x * i - y * (n - i + 1) == 0
    // arr[i] == x * i + y * (n - i + 1)
    // let's i = 1, n, then x = (n * arr[n] - arr[1])/(n^2 - 1), y = (n * arr[1] - arr[n])/(n^2 - 1)
    ll x, y;
    if (((n * arr[n] - arr[1]) % (n * n - 1) == 0) && ((n * arr[n] - arr[1]) / (n * n - 1) >= 0))
        x = (n * arr[n] - arr[1]) / (n * n - 1);
    else
        return false;
    if (((n * arr[1] - arr[n]) % (n * n - 1) == 0) && ((n * arr[1] - arr[n]) / (n * n - 1) >= 0))
        y = (n * arr[1] - arr[n]) / (n * n - 1);
    else
        return false;

    for (ll i = 1; i <= n; i++)
    {
        if (arr[i] != x * i + y * (n - i + 1))
            return false;
    }
    return true;
}
signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        cout << (solve() ? "YES" : "NO") << endl;
    }
}