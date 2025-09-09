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
    for (int i = 0; i < n; ++i)
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
    for (int i = 1; i < len + 1; ++i)
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
void solve()
{
    ll n;
    cin >> n;
    vl a(n), b(n);
    ll sum = 0, sm = 0;

    // sm = f(a)
    for (ll i = 0; i < n; i++)
        cin >> a[i], sum ^= a[i], sm ^= a[i];
    // sum = f(a) ^ f(b)
    for (ll i = 0; i < n; i++)
        cin >> b[i], sum ^= b[i];

    vl c(bit + 5, 0);

    auto insert = [&](ll x)
    {
        for (ll i = bit; i > -1; i--)
        {
            if (x >> i & 1)
            {
                if (!c[i])
                {
                    c[i] = x;
                    return;
                }
                else
                    x ^= c[i];
            }
        }
    };

    for (ll i = 0; i < n; i++)
    {
        insert(a[i] ^ b[i]);
    }

    bool ok = false;
    for (ll i = bit; i > -1; i--)
    {
        // no linear basis, continue
        if (c[i])
        {
            // a[i] = b[i]
            if (!((sum >> i) & 1))
            {
                // a[i] = 1
                if ((sm >> i) & 1)
                    sm ^= c[i];
            }
            else
            {
                // the first position a[i] != b[i]
                ll ans = LLONG_MAX;
                // 1.don't use c[i]; 2.use c[i]
                for (auto v : {sm, sm ^ c[i]})
                {
                    for (ll j = i - 1; j > -1; j--)
                    {
                        v = min(v, v ^ c[j]);
                    }
                    ans = min(ans, max(v, sum ^ v));
                }
                cout << ans << '\n';
                ok = true;
                break;
            }
        }
    }

    if (!ok)
    {
        cout << max(sm, sm ^ sum) << '\n';
    }
}