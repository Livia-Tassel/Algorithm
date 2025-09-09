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
using vb = vector<bool>;

ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}
vl invs(mod + 1);
void inv()
{
    invs[1] = 1;
    for (int i = 2; i < mod; i++)
    {
        invs[i] = mod - invs[mod % i] * (mod / i) % mod;
    }
}
vvl mat(1001, vl(1001));
void gauss(ll n)
{
    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < n + 1; j++)
        {
            if (j < i && mat[j][j] != 0)
            {
                continue;
            }
            if (mat[j][i] != 0)
            {
                swap(mat[i], mat[j]);
                break;
            }
        }
        if (mat[i][i] != 0)
        {
            for (ll j = 1; j < n + 1; j++)
            {
                if (i != j && mat[j][i] != 0)
                {
                    ll g = gcd(mat[j][i], mat[i][i]);
                    ll a = mat[i][i] / g;
                    ll b = mat[j][i] / g;
                    if (j < i && mat[j][j] != 0)
                    {
                        for (ll k = j; k < i; k++)
                        {
                            mat[j][k] = (mat[j][k] * a) % mod;
                        }
                        // mat[j][j] = (mat[j][j] * a) % mod; assume all the free variables are 0
                    }
                    for (ll k = i; k < n + 2; k++)
                    {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % mod + mod) % mod;
                    }
                }
            }
        }
    }
    for (ll i = 1; i < n + 1; i++)
    {
        if (mat[i][i] != 0)
        {
            bool flag = false;
            for (ll j = i + 1; j <= n; j++)
            {
                if (mat[i][j] != 0)
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                mat[i][n + 1] = (mat[i][n + 1] * invs[mat[i][i]]) % mod;
                mat[i][i] = 1;
            }
        }
    }
}

// n x m grid with initial values of 0, 1, or 2, brushing a cell (i, j) adds +2 to its value and +1 to its neighbors, all modulo 3, return one of the methods to make all cells have a final value of 0.
const ll mod = 3;
ll n, m, s;
void build(vvl &grid)
{
    ll dir[] = {0, -1, 0, 1, 0};
    for (ll i = 1; i < s + 1; i++)
    {
        for (ll j = 1; j < s + 2; j++)
        {
            mat[i][j] = 0;
        }
    }
    ll cur, row, col;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            cur = i * m + j + 1;
            mat[cur][cur] = 2;
            for (ll d = 0; d < 4; d++)
            {
                row = i + dir[d];
                col = j + dir[d + 1];
                if (row > -1 && row < n && col > -1 && col < m)
                {
                    mat[cur][row * m + col + 1] = 1;
                }
            }
            mat[cur][s + 1] = (3 - grid[i][j]) % mod;
        }
    }
}

ll brush(vvl &grid)
{
    cin >> n >> m;
    s = n * m;
    build(grid);
    gauss(s);

    // simply assume all free variables are not operated on.
    // for (ll i = 1; i < s + 1; i++)
    // {
    //     if (mat[i][i] != 0)
    //     {
    //         mat[i][s + 1] = (mat[i][s + 1] * invs[mat[i][i]]) % mod;
    //     }
    // }
    // ans += mat[i][s + 1];
}

// given n tools and m records, each record contains a set of tools and information about their total manufacturing days, the manufacturing time for each tool is a fixed integer between 3 and 9 days, determine if the records are contradictory, have multiple solutions, or a unique solution, and print the corresponding result.
const ll mod = 7;
ll n, m;
void build()
{
    for (ll i = 1; i < s + 1; i++)
    {
        for (ll j = 1; j < s + 2; j++)
        {
            mat[i][j] = 0;
        }
    }
}

ll tool()
{
    cin >> n >> m;
    s = max(n, m);
    build();
    for (ll i = 1; i < m + 1; i++)
    {
        ll k, sta, end, x;
        cin >> k >> sta >> end;
        while (k--)
        {
            cin >> x;
            mat[i][x] = (mat[i][x] + 1) % mod;
        }
        mat[i][s + 1] = ((end - sta + 1) % mod + mod) % mod;
    }
    gauss(s);

    ll sign = 1;
    for (ll i = 1; i < s + 1; i++)
    {
        if (mat[i][i] == 0 && mat[i][s + 1] != 0)
        {
            sign = -1;
            break;
        }
        if (i < n + 1 && mat[i][i] == 0)
        {
            sign = 0;
        }
    }

    if (sign == 1)
    {
        for (ll i = 1; i < n + 1; i++)
        {
            if (mat[i][s + 1] < 3)
            {
                cout << mat[i][s + 1] + 7 << " ";
            }
            else
            {
                cout << mat[i][s + 1] << " ";
            }
        }
    }
    else
    {
        cout << sign << endl;
    }
}