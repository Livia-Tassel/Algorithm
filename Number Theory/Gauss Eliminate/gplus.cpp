#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <iomanip>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;
using vs = vector<string>;
using vvd = vector<vector<double>>;
using vd = vector<double>;
const ll mod = 1e9 + 7;
const double sml = 1e-7;

vvd mat(101, vd(101));
// n^3
void gauss(ll n)
{
    // n x n+1
    for (ll i = 1; i < n + 1; i++)
    {
        ll max = i;
        for (ll j = 1; j < n + 1; j++)
        {
            if (j < i && abs(mat[j][j]) >= sml)
            {
                continue;
            }
            if (abs(mat[j][i]) > abs(mat[max][i]))
            {
                max = j;
            }
        }
        swap(mat[i], mat[max]);

        if (abs(mat[i][i]) >= sml)
        {
            double t = mat[i][i];
            for (ll j = i; j < n + 2; j++)
            {
                mat[i][j] /= t;
            }
            for (ll j = 1; j < n + 1; j++)
            {
                if (i != j)
                {
                    double rate = mat[j][i] / mat[i][i];
                    for (ll k = i; k < n + 2; k++)
                    {
                        mat[j][k] -= mat[i][k] * rate;
                    }
                }
            }
        }
    }
}
// absolutely no dependency within the pivot variables or the free variables; free variables do not depend on pivot variables, but the values of the pivot variables may depend on the values of some free variables.

void print(ll n)
{
    ll sign = 1; // 1: unique solution, 0: many solutions, -1: no solution

    for (ll i = 1; i < n + 1; i++)
    {
        if (abs(mat[i][i]) < sml && abs(mat[i][n + 1]) >= sml)
        {
            sign = -1;
            break;
        }
        if (abs(mat[i][i]) < sml)
        {
            sign = 0;
        }
    }

    if (sign == 1)
    {
        for (ll i = 1; i < n + 1; i++)
        {
            cout << "x_" << i << "="
                 << fixed << setprecision(2) << mat[i][n + 1] << "\n";
        }
    }
    else
    {
        cout << sign << "\n";
    }
}

// signed main()
// {
//     ll n;
//     cin >> n;
//     for (ll i = 1; i < n + 1; i++)
//     {
//         for (ll j = 1; j < n + 2; j++)
//         {
//             cin >> mat[i][j];
//         }
//     }
//     gauss(n);
//     print(n);
// }

// n+1 points in n-dimensional space, each with n coordinates, assuming these points all lie on the surface of a sphere, find the coordinates of the center of the sphere.
vvd data(101, vd(101));
void solve(ll n)
{
    for (ll i = 1; i < n + 2; i++)
    {
        for (ll j = 1; j < n + 1; j++)
        {
            cin >> data[i][j];
        }
    }

    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < n + 1; j++)
        {
            mat[i][j] = 2 * (data[i][j] - data[i + 1][j]);
            mat[i][n + 1] += data[i][j] * data[i][j] - data[i + 1][j] * data[i + 1][j];
        }
    }
    gauss(n);
    for (ll i = 1; i < n + 1; i++)
    {
        cout << fixed << setprecision(3) << mat[i][n + 1] << "\n";
    }
}

// n^4
// n items with positive integer weights, where there is exactly one heaviest item, have n+1 weighing data points, of which exactly one is incorrect, find the number of the heaviest item, if the data is invalid, return "illegal".