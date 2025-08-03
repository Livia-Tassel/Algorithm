#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define ll long long
using namespace std;

const ll MAXN = 1001;
ll diff[MAXN][MAXN];

ll get_diff(ll i, ll j)
{
    return i < 0 || j < 0 ? 0 : diff[i][j];
}

ll sum_diff(ll a, ll b, ll c, ll d)
{
    return a > c ? 0 : get_diff(c, d) - get_diff(a - 1, d) - get_diff(c, b - 1) + get_diff(a - 1, b - 1);
}

// recommended to pass two-dimensional arrays using vector
void add(ll a, ll b, ll c, ll d, ll x)
{
    diff[a][b] += x;
    diff[c + 1][b] -= x;
    diff[a][d + 1] -= x;
    diff[c + 1][d + 1] += x;
}

void build_diff(ll n, ll m)
{
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            ll x;
            cin >> x;
            // add the value x to the rectangle defined by (i, j) to (i, j)
            // equal to adding x to the cell (i, j)
            add(i, j, i, j, x);
        }
    }
}

void build_prefix(ll n, ll m)
{
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
        }
    }
}

signed main()
{
    ll n, m, q;
    cin >> n >> m >> q;

    build_diff(n, m);
    for (ll i = 0; i < q; i++)
    {
        ll a, b, c, d, k;
        cin >> a >> b >> c >> d >> k;
        // modify the rectangle defined by (a, b) to (c, d) by k
        add(a, b, c, d, k);
    }
    // diff[n][m] padding with zeros to reduce boundary checks
    build_prefix(n, m);

    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            cout << diff[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}