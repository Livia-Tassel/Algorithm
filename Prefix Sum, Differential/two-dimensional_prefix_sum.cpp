#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define ll long long
using namespace std;

ll matrix[4][4] = {
    {1, 1, 0, 1},
    {0, 1, 1, 1},
    {0, 1, 0, 1},
    {1, 1, 0, 1}};
ll get_matrix(ll i, ll j)
{
    return i < 0 || j < 0 ? 0 : matrix[i][j];
}
ll sum_matrix(ll a, ll b, ll c, ll d)
{
    return a > c ? 0 : get_matrix(c, d) - get_matrix(a - 1, d) - get_matrix(c, b - 1) + get_matrix(a - 1, b - 1);
}

signed main()
{
    // 2D Prefix Sum
    // sum[i][j] = sum(arr[0][0] to arr[i][j])
    ll arr[3][3] = {
        {3, 1, -2},
        {5, -3, 4},
        {3, 6, -2}};
    ll sum[3][3] = {0};
    // 容斥 sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + arr[i][j]
    for (ll i = 0; i < 3; i++)
    {
        for (ll j = 0; j < 3; j++)
        {
            sum[i][j] = arr[i][j];
            if (i > 0)
                sum[i][j] += sum[i - 1][j];
            if (j > 0)
                sum[i][j] += sum[i][j - 1];
            if (i > 0 && j > 0)
                sum[i][j] -= sum[i - 1][j - 1];
        }
    }

    // for (ll i = 0; i < 3; i++)
    // {
    //     for (ll j = 0; j < 3; j++)
    //     {
    //         cout << sum[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // sum of submatrix (x1, y1) to (x2, y2)
    // sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1]
    ll x1 = 1, y1 = 1, x2 = 2, y2 = 2;
    ll result = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];

    // verify if the borders of a sub-square in 0/1 matrix are all 1s.
    ll max_border;
    ll n = sizeof(matrix) / sizeof(matrix[0]);       // rows
    ll m = sizeof(matrix[0]) / sizeof(matrix[0][0]); // cols
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            matrix[i][j] += get_matrix(i - 1, j) + get_matrix(i, j - 1) - get_matrix(i - 1, j - 1);
        }
    }
    if (matrix[n - 1][m - 1] == 0)
    {
        max_border = 0;
    }
    else
    {
        max_border = 1;
        // check matrix[a][b] to matrix[c][d] is a sub-square
        for (ll a = 0; a < n; a++)
        {
            for (ll b = 0; b < m; b++)
            {
                for (ll c = a + max_border, d = b + max_border, k = max_border + 1; c < n && d < m; c++, d++, k++)
                {

                    // sum of submatrix (a, b) to (c, d) - sum of submatrix (a+1, b+1) to (c-1, d-1)
                    if (sum_matrix(a, b, c, d) - sum_matrix(a + 1, b + 1, c - 1, d - 1) == (k - 1) << 2)
                    {
                        max_border = k;
                    }
                }
            }
        }
    }
    cout << max_border << endl;

    return 0;
}