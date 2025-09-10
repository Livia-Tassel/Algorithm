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
using vd = vector<double>;
using vb = vector<bool>;
const ll mod = 1e9 + 7;
const ll maxn = 101;
const ll bit = 63;
const ll sml = 10e-7;
// vl arr(maxn), basis(bit + 1, 0);
// ll n, flag;
// bool insert(ll x)
// {
//     for (ll i = bit; i > -1; i--)
//     {
//         if ((x >> i) & 1)
//         {
//             if (basis[i] == 0)
//             {
//                 basis[i] = x;
//                 return true;
//             }
//             x ^= basis[i];
//         }
//     }
//     return false;
// }
// void build()
// {
//     flag = 0;
//     for (ll i = 1; i < n + 1; i++)
//     {
//         if (!insert(arr[i]))
//         {
//             flag = 1;
//         }
//     }
// }

// gauss elimination to solve the linear basis
ll len, n, flag;
vl arr(maxn), basis(maxn, 0);
void gbuild()
{
    for (ll i = 0; i < n; ++i)
    {
        basis[i + 1] = arr[i];
    }
    len = 1;
    for (ll i = bit; i > -1; i--)
    {
        for (ll j = len; j < n + 1; j++)
        {
            if ((basis[j] & (1L << i)) != 0)
            {
                swap(basis[j], basis[len]);
                break;
            }
        }
        if ((basis[len] & (1L << i)) != 0)
        {
            for (ll j = 1; j < n + 1; j++)
            {
                if (j != len && (basis[j] & (1L << i)) != 0)
                {
                    basis[j] ^= basis[len];
                }
            }
            len++;
        }
    }
    len--;
    flag = (len != n ? 1 : 0);
}
ll kx(ll k)
{
    vl cb;
    for (ll i = 1; i < len + 1; ++i)
    {
        if (basis[i] > 0)
        {
            cb.push_back(basis[i]);
        }
    }
    sort(cb.begin(), cb.end());

    if (k > (1LL << len) - 1)
    {
        return -1;
    }

    ll ans = 0;
    for (ll i = 0; i < len; ++i)
    {
        if ((k >> i) & 1)
        {
            ans ^= cb[i];
        }
    }
    return ans;
}

// 2024 CCPC Online Contest
ll n;
vl a(maxn), b(maxn), p(bit, 0);
void insert(ll x)
{
    for (ll i = bit - 1; i > -1; i--)
    {
        if ((x >> i) & 1)
        {
            if (!p[i])
            {
                p[i] = x;
                break;
            }
            x ^= p[i];
        }
    }
}

void solve()
{
    cin >> n;
    ll sa = 0, sb = 0;
    for (ll i = 1; i < n + 1; i++)
    {
        cin >> a[i];
        sa ^= a[i];
    }
    for (ll i = 1; i < n + 1; i++)
    {
        cin >> b[i];
        sb ^= b[i];
        insert(a[i] ^ b[i]);
    }
    for (ll i = bit - 1; i > -1; i--)
    {
        ll xa = sa ^ p[i];
        ll xb = sb ^ p[i];
        if (max(xa, xb) < max(sa, sb))
        {
            sa = xa, sb = xb;
        }
    }
    cout << max(sa, sb) << '\n';
}

// // vector linear basis
// ll n, m;
// vvl mat(maxn, vl(maxn));
// bool insert(ll i)
// {
//     for (ll j = 1; j < m + 1; j++)
//     {
//         if (abs(mat[i][j]) >= sml)
//         {
//             if (basis[j] == 0)
//             {
//                 basis[j] = i;
//                 return true;
//             }
//             double rate = mat[i][j] / mat[basis[j]][j];
//             for (ll k = j; k < m + 1; k++)
//             {
//                 mat[i][k] -= rate * mat[basis[j]][k];
//             }
//         }
//     }
//     return false;
// }