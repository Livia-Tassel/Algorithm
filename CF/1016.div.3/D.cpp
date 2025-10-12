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
    cout.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}