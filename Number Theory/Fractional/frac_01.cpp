#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;
using vvd = vector<vector<double>>;
using vd = vector<double>;
using vl = vector<ll>;
const ll mod = 1e9 + 7;
const ll maxn = 1e5 + 1;
const ll sml = 10e-7;

// n points (a, b) and discard k points, find the maximum value of the ratio sum(a) / sum(b) for the remaining n-k points, the final result should be (ratio * 100) rounded to the nearest integer.
vvd arr(maxn, vd(3)); // arr[i][0] = ai, arr[i][1] = bi, arr[i][2] = ai - xbi
ll n, k;
bool check(double m)
{
    for (ll i = 0; i < n; i++)
    {
        arr[i][2] = arr[i][0] - m * arr[i][1];
    }
    sort(arr.begin(), arr.begin() + n, [](const vd &a, const vd &b)
         { return a[2] > b[2]; });

    double sum = 0;
    for (ll i = 0; i < k; i++)
    {
        sum += arr[i][2];
    }

    return sum >= 0;
}
void solve()
{
    // (a1 + a2 + a3)/(b1 + b2 + b3) = x
    // (a1 - xb1) + (a2 - xb2) + (a3 - xb3) = 0
    // binary check x for (a1 - xb1) + (a2 - xb2) + (a3 - xb3) >= 0
    while (n != 0 || k != 0)
    {
        k = n - k;
        double l = 0, r = 0, m;
        for (ll i = 0; i < n; i++)
        {
            cin >> arr[i][0];
            r += arr[i][0];
        }
        for (ll i = 0; i < n; i++)
        {
            cin >> arr[i][1];
        }

        double ans = 0;
        while (l < r && r - l >= sml)
        {
            m = (l + r) / 2;
            if (check(m))
            {
                ans = m;
                l = m + sml;
            }
            else
            {
                r = m - sml;
            }
        }
        cout << (ll)(100 * (ans + 0.005));
    }
}