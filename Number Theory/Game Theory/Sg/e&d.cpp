#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <cstring>
#define ll long long
using namespace std;

// two piles of stones with quantities a and b, move consists of the following steps:
// chooses one pile and removes it, then splits the other pile into two new piles, x and y, where x and y are positive integers.

// both new piles must have a quantity greater than 0, if can't, that player loses.
ll dp[1001][1001];
void build()
{
    memset(dp, -1, sizeof(dp));
}
ll loz(ll status)
{
    ll cnt = 0;
    while ((status & 1) != 0)
    {
        status >>= 1;
        cnt++;
    }
    return cnt;
}
ll sg(ll a, ll b)
{
    if (a == 1 && b == 1)
    {
        return 0;
    }
    if (dp[a][b] != -1)
    {
        return dp[a][b];
    }
    vector<bool> appear(max(a, b) + 1, false);
    if (a > 1)
    {
        for (ll l = 1, r = a - 1; l < a; l++, r--)
        {
            appear[sg(l, r)] = true;
        }
    }
    if (b > 1)
    {
        for (ll l = 1, r = b - 1; l < b; l++, r--)
        {
            appear[sg(l, r)] = true;
        }
    }
    ll ans = 0;
    for (ll s = 0; s <= max(a, b); s++)
    {
        if (!appear[s])
        {
            ans = s;
            break;
        }
    }
    dp[a][b] = ans;
    return ans;
}

// void sg_cnt()
// {
//     cout << endl;
//     cout << "    ";
//     for (ll i = 1; i <= 9; i++)
//     {
//         cout << setw(2) << i;
//     }
//     cout << endl
//          << endl;
//     for (ll a = 1; a <= 9; a++)
//     {
//         cout << a << "   ";
//         for (ll b = 1; b < a; b++)
//         {
//             cout << " x";
//         }
//         for (ll b = a; b <= 9; b++)
//         {
//             cout << setw(2) << sg(a, b);
//         }
//         cout << endl;
//     }
// }

// void sg_mone()
// {
//     cout << endl;
//     cout << "    ";
//     for (ll i = 0; i <= 8; i++)
//     {
//         cout << setw(2) << i;
//     }
//     cout << endl
//          << endl;
//     for (ll a = 1; a <= 9; a++)
//     {
//         cout << (a - 1) << "   ";
//         for (ll b = 1; b < a; b++)
//         {
//             cout << " x";
//         }
//         for (ll b = a; b <= 9; b++)
//         {
//             cout << setw(2) << sg(a, b);
//         }
//         cout << endl;
//     }
// }

void prove()
{
    cout << "Test Start!" << endl;
    for (ll a = 1; a < 1001; a++)
    {
        for (ll b = 1; b < 1001; b++)
        {
            if (sg(a, b) != loz((a - 1) | (b - 1)))
            {
                cout << "error!" << endl;
                return;
            }
        }
    }
    cout << "Test Over!" << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    build();
    // sg_cnt();
    // sg_mone();

    return 0;
}