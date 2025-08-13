#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define ll long long
using namespace std;

const ll MAXN = 1001;
ll field[MAXN][MAXN];
ll diff[MAXN][MAXN];

ll _sort(ll arr[], ll n)
{
    sort(arr, arr + 2 * n);
    ll size = 1;
    for (ll i = 1; i < 2 * n; i++)
    {
        if (arr[i] != arr[i - 1])
        {
            arr[size++] = arr[i];
        }
    }
    return size;
}

ll _rank(ll arr[], ll n, ll x)
{
    // return the index of the first element greater than or equal to x
    return lower_bound(arr, arr + n, x) - arr + 1;
}

void add(ll a, ll b, ll c, ll d, ll x)
{
    diff[a][b] += x;
    diff[c + 1][b] -= x;
    diff[a][d + 1] -= x;
    diff[c + 1][d + 1] += x;
}

signed main()
{
    // field[[x, y ,r], ...]
    ll n, x, y, r;
    cin >> n;
    // n rectangles, 2n coordinates
    ll fx[n << 1], fy[n << 1];
    for (ll i = 0, k = 0, p = 0; i < n; i++)
    {
        x = field[i][0];
        y = field[i][1];
        r = field[i][2];
        // x := 2x, y := 2y, r := 2r
        fx[k++] = 2 * x - r;
        fx[k++] = 2 * x + r;
        fy[p++] = 2 * y - r;
        fy[p++] = 2 * y + r;
    }

    // discretize the coordinates
    ll sizex = _sort(fx, n);
    ll sizey = _sort(fy, n);

    // two-dimensional_differential
    ll diff_row = sizex + 2;
    ll diff_col = sizey + 2;

    for (ll i = 0, a, b, c, d; i < n; i++)
    {
        x = field[i][0];
        y = field[i][1];
        r = field[i][2];
        a = _rank(fx, sizex, 2 * x - r);
        b = _rank(fy, sizey, 2 * y - r);
        c = _rank(fx, sizex, 2 * x + r);
        d = _rank(fy, sizey, 2 * y + r);
        add(a, b, c, d, 1);
    }

    ll ans = 0;
    for (ll i = 1; i <= diff_row; i++)
    {
        for (ll j = 1; j <= diff_col; j++)
        {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            ans = max(ans, diff[i][j]);
        }
    }
    cout << ans << endl;
    return 0;
}