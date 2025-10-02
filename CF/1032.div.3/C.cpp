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
using vvl = vector<vector<ll>>;

void solve(ll n, ll m)
{
    vvl mat(n + 1, vl(m + 1, 0));
    ll max = 0, cnt = 0;
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            cin >> mat[i][j];
            if (mat[i][j] > max)
            {
                max = mat[i][j], cnt = 1;
            }
            else if (mat[i][j] == max)
            {
                cnt++;
            }
        }
    }

    vl row(n + 1, 0), col(m + 1, 0);
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            if (mat[i][j] == max)
            {
                row[i]++, col[j]++;
            }
        }
    }

    ll flag = 0;
    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            if (row[i] + col[j] - (mat[i][j] == max) == cnt)
            {
                flag = 1;
            }
        }
    }
    cout << max - flag << endl;
}

signed main()
{
    ll t, n, m;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        solve(n, m);
    }
}