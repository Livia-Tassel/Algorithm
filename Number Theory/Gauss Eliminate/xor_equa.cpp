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
using vb = vector<bool>;
const ll mod = 1e9 + 7;
const double sml = 1e-7;
const ll maxv = 2001;

// vvl mat(101, vl(101));
void gauss(ll n)
{
    // n x n+1
    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < n + 1; j++)
        {
            if (j < i && mat[j][j] == 1)
            {
                continue;
            }
            if (mat[j][i] == 1)
            {
                swap(mat[i], mat[j]);
                break;
            }
        }

        if (mat[i][i] == 1)
        {
            for (ll j = 1; j < n + 1; j++)
            {
                if (i != j && mat[j][i] == 1)
                {
                    for (ll k = i; k < n + 2; k++)
                    {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}

// the prime factors of each number do not exceed 2000, find the number of non-empty subsets of arr whose elements' product is a perfect square.
vvl mat(maxv, vl(maxv));
vl arr(305), prime(305), pt(305);
vb vis(maxv, false);
ll cnt;
ll build()
{
    for (ll i = 2; i * i < maxv; i++)
    {
        if (!vis[i])
        {
            for (ll j = i * i; j < maxv; j += i)
            {
                vis[j] = true;
            }
        }
    }
    cnt = 0;
    for (ll i = 2; i < maxv; i++)
    {
        if (!vis[i])
        {
            prime[++cnt] = i; // 303
        }
    }

    pt[0] = 1; // 2^i % mod
    for (ll i = 1; i < 305; i++)
    {
        pt[i] = (2 * pt[i - 1]) % mod;
    }
}
ll square(ll n)
{
    // arr[] = {12, 8, 6, 60, 21}
    //     2 3 5 7
    // 12: 0 1 0 0
    //  8: 1 0 0 0
    //  6: 1 1 0 0
    // 60: 0 1 1 0
    // 21: 0 1 0 1
    build();
    for (auto &row : mat)
    {
        fill(row.begin(), row.end(), 0);
    }
    ll cur;
    for (ll i = 1; i < n + 1; i++)
    {
        cur = arr[i];
        for (ll j = 1; j < cnt + 1 && cur != 0; j++)
        {
            while (cur % prime[j] == 0)
            {
                mat[j][i] ^= 1;
                cur /= prime[j];
            }
        }
    }

    gauss(cnt);
    ll pivot = 0;
    for (ll i = 1; i < cnt + 1; i++)
    {
        if (mat[i][i] == 1)
        {
            pivot++;
        }
    }

    return pt[n - pivot] - 1;
}
signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        for (ll i = 1; i < n + 1; i++)
        {
            cin >> arr[i];
        }
        cout << square(n) << endl;
    }
}

// n nodes and m undirected edges, the state of every node is 0, perform an operation on any node to flip its state and the state of all its adjacent nodes, the minimum step to make all nodes become 1.
vl op(maxv);
ll ans, n;
void dfs(ll i, ll num)
{
    if (num > ans - 1)
    {
        return;
    }
    // 1 ~ n, points have been determined.
    if (i == 0)
    {
        ans = num;
    }
    else
    {
        if (mat[i][i] == 0)
        {
            op[i] = 0;
            dfs(i - 1, num);
            op[i] = 1;
            dfs(i - 1, num + 1);
        }
        else
        {
            ll cur = mat[i][n + 1];
            for (ll j = i + 1; j < n + 1; j++)
            {
                if (mat[i][j] == 1)
                {
                    cur ^= op[j];
                }
            }
            dfs(i - 1, num + cur);
        }
    }
}
void build(ll n)
{
    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = 1; j < n + 1; j++)
        {
            mat[i][j] = 0;
        }
        mat[i][i] = 1;
        mat[i][n + 1] = 1;
        op[i] = 0;
    }
}

void flip(ll n, ll m)
{
    build(n);
    for (ll i = 0; i < m; i++)
    {
        ll u, v;
        cin >> u >> v;
        mat[u][v] = 1;
        mat[v][u] = 1;
    }
    gauss(n);

    ll sign = 1;
    for (ll i = 1; i < n + 1; i++)
    {
        if (mat[i][i] == 0)
        {
            sign = 0;
            break;
        }
    }
    ans = 0;
    if (sign)
    {
        for (ll i = 1; i < n + 1; i++)
        {
            ans += mat[i][n + 1];
        }
    }
    else
    {
        ans = n;
        dfs(n, 0);
    }
    cout << ans << endl;
}

// given n insects and m consistent measurement records, each record consists of a set of insects and the parity of their total number of legs, find the minimum number of records k required to uniquely determine the parity of each insect's legs.
const ll bit = 64;
const ll maxn = maxv / bit + 1;
vvl mat(maxn, vl(maxn));
ll n, m, s, k;
void eor(ll ro, ll rt, ll bits)
{
    for (ll k = 0; k <= bits / bit; k++)
    {
        mat[rt][k] ^= mat[ro][k];
    }
}
void gauss(ll n)
{
    k = 0;
    for (ll i = 1; i < n + 1; i++)
    {
        for (ll j = i; j < n + 1; j++)
        {
            if (get(j, i) == 1)
            {
                swap(mat[i], mat[j]);
                k = max(k, j);
                break;
            }
        }
        if (get(i, i) == 0)
        {
            return;
        }
        for (ll j = 1; j < n + 1; j++)
        {
            if (i != j && get(j, i) == 1)
            {
                eor(i, j, n + 2);
            }
        }
    }
}
void setb(ll row, ll col, ll v)
{
    if (v == 0)
    {
        mat[row][col / bit] &= ~(1LL << (col % bit));
    }
    else
    {
        mat[row][col / bit] |= 1LL << (col % bit);
    }
}
ll get(ll row, ll col)
{
    return ((mat[row][col / bit] >> (col % bit)) & 1) == 1 ? 1 : 0;
}
ll legs()
{
    cin >> n >> m;
    s = max(n, m);

    for (ll i = 1; i < m + 1; i++)
    {
        ll lg;
        string sta;
        cin >> sta >> lg;
        for (ll j = 1; j < n + 1; j++)
        {
            setb(i, j, sta[j - 1] - '0');
        }
        setb(i, s + 1, lg);
    }
    gauss(s);

    ll sign = 1;
    for (ll i = 1; i < n + 1; i++)
    {
        if (get(i, i) == 0)
        {
            sign = 0;
            break;
        }
    }
    if (sign == 0)
    {
        cout << "Cannot Determine" << endl;
    }
    else
    {
        cout << k << endl;
        for (ll i = 1; i < n + 1; i++)
        {
            if (get(i, s + 1) == 1)
            {
                cout << "Moon" << endl;
            }
            else
            {
                cout << "Earth" << endl;
            }
        }
    }
}