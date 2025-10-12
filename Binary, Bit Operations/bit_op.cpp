#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define ll long long
using namespace std;

bool power_of_two(ll n)
{
    return n > 0 && n == (n & -n);
}

ll min_power_of_two(ll n)
{
    // return the smallest power of two greater than or equal to n
    if (n <= 0)
        return 1;

    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16; // for 32-bit
    n |= n >> 32; // for 64-bit
    return n + 1;
}

ll and_of_all_nums(ll left, ll right)
{
    while (left < right)
    {
        right -= (right & -right); // clear the lowest set bit of right
    }
    return right;
}

ll reversed_binary(ll n)
{
    n = (n & 0x5555555555555555LL) << 1 | (n & 0xAAAAAAAAAAAAAAAALL) >> 1; // 1 bit groups
    n = (n & 0x3333333333333333LL) << 2 | (n & 0xCCCCCCCCCCCCCCCCLL) >> 2; // 2 bit groups
    n = (n & 0x0F0F0F0F0F0F0F0FLL) << 4 | (n & 0xF0F0F0F0F0F0F0F0LL) >> 4; // 4 bit groups
    n = (n & 0x00FF00FF00FF00FFLL) << 8 | (n & 0xFF00FF00FF00FF00LL) >> 8; // 8 bit groups (for 32-bit)
    n = (n & 0x0000FFFF0000FFFFLL) << 16 | (n & 0xFFFF0000FFFF0000LL) >> 16; // 16 bit groups (for 64-bit)

    // 32 bit groups
    n = (n >> 32) | (n << 32); // n = (n >> 16) | (n << 16); // for 32-bit, n > 0

    return n;
}

ll nums_of_one(ll n)
{
    n = (n & 0x5555555555555555LL) + ((n >> 1) & 0x5555555555555555LL);
    n = (n & 0x3333333333333333LL) + ((n >> 2) & 0x3333333333333333LL);
    n = (n & 0x0F0F0F0F0F0F0F0FLL) + ((n >> 4) & 0x0F0F0F0F0F0F0F0FLL);
    n = (n & 0x00FF00FF00FF00FFLL) + ((n >> 8) & 0x00FF00FF00FF00FFLL);
    n = (n & 0x0000FFFF0000FFFFLL) + ((n >> 16) & 0x0000FFFF0000FFFFLL);
    n = (n & 0x00000000FFFFFFFFLL) + ((n >> 32) & 0x00000000FFFFFFFFLL);
    return n;
}

//  1  4 13 16
//  3  2 15 14
//  9 12  5  8
// 11 10  7  6 ...
//  ...
void solve()
{
    ll n;
    cin >> n;
    ll q;
    cin >> q;
    while (q--)
    {
        string s;
        cin >> s;

        if (s == "->")
        {
            ll a, b;
            cin >> a >> b;

            ll row = a - 1;
            ll col = b - 1;
            ll ans = 0;

            // from the most significant level (n-1) down to 0
            // n = 2, (0, 0) to (3, 3), also (00, 00) to (11, 11)
            for (ll i = n - 1; i >= 0; --i)
            {
                // the i-th bit from row and column
                ll row_bit = (row >> i) & 1;
                ll col_bit = (col >> i) & 1;

                ll dg = 0;

                if (row_bit == 0 && col_bit == 0)
                    dg = 0; // Top-Left
                else if (row_bit == 1 && col_bit == 1)
                    dg = 1; // Bottom-Right
                else if (row_bit == 1 && col_bit == 0)
                    dg = 2; // Bottom-Left
                else if (row_bit == 0 && col_bit == 1)
                    dg = 3; // Top-Right

                // ans = 4 * ans + dg
                ans = (ans << 2) | dg;
            }
            cout << ans + 1 << endl;
        }
        else
        {
            ll d;
            cin >> d;

            ll val = d - 1;
            ll a = 0, b = 0;

            for (ll i = n - 1; i >= 0; --i)
            {
                // 010000 -> 01
                ll dg = (val >> (2 * i));
                // 010000 & 001111 -> 0000
                val &= (1LL << (2 * i)) - 1;

                ll row_bit = 0, col_bit = 0;
                if (dg == 0)
                {
                    row_bit = 0;
                    col_bit = 0;
                } // Top-Left
                else if (dg == 1)
                {
                    row_bit = 1;
                    col_bit = 1;
                } // Bottom-Right
                else if (dg == 2)
                {
                    row_bit = 1;
                    col_bit = 0;
                } // Bottom-Left
                else if (dg == 3)
                {
                    row_bit = 0;
                    col_bit = 1;
                } // Top-Right

                a = (a << 1) | row_bit;
                b = (b << 1) | col_bit;
            }
            cout << a + 1 << " " << b + 1 << endl;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cout << min_power_of_two(-9) << endl;
    cout << and_of_all_nums(13, 15) << endl;
    cout << reversed_binary(13LL) << endl;
    cout << nums_of_one(13LL) << endl; // 3

    return 0;
}