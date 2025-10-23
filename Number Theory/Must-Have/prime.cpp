#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <random>
using namespace std;
#define ll long long
using vl = vector<ll>;
using vvl = vector<vl>;

#define vp(a)              \
    cout << #a << " = ";   \
    for (auto aa : a)      \
        cout << aa << " "; \
    cout << "\n";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

// typedef __int128 ll;
bool is_prime(ll x)
{
    if (x <= 1)
    {
        return false;
    }
    for (ll i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }
    return true;
}

// template <typename ll>
inline ll read()
{
    ll x = 0, f = 1;
    char ch = 0;
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;
    for (; isdigit(ch); ch = getchar())
        x = (x << 3) + (x << 1) + (ch - '0');
    return x * f;
}

// template <typename ll>
inline void write(ll x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

// template <typename ll>
inline void print(ll x, char ed = '\n')
{
    write(x), putchar(ed);
}

ll t, n;

ll qpow(ll a, ll b, ll mod)
{
    ll ret = 1;
    while (b)
    {
        if (b & 1)
            ret = (ret * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ret % mod;
}

vector<ll> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

// s * (logn)^3
bool miller_rabin(ll n)
{
    if (n < 3 || n % 2 == 0)
        return n == 2;
    ll u = n - 1, t = 0;
    while (u % 2 == 0)
        u /= 2, ++t;
    for (auto a : p)
    {
        if (n == a)
            return 1;
        if (n % a == 0)
            return 0;
        ll v = qpow(a, u, n);
        if (v == 1)
            continue;
        ll s = 1;
        for (; s <= t; ++s)
        {
            if (v == n - 1)
                break;
            v = v * v % n;
        }
        if (s > t)
            return 0;
    }
    return 1;
}

signed main()
{
    t = read(); // t = read<ll>();
    while (t--)
    {
        n = read(); // n = read<ll>();
        if (miller_rabin(n))
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}

// safe qpow
ll mul(ll a, ll b, ll mod)
{
    ll ans = 0;
    a %= mod;
    while (b > 0)
    {
        if (b & 1)
        {
            ans = (ans + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}
ll qpow(ll x, ll n, ll mod)
{
    ll ans = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ans = mul(ans, x, mod);
        }
        x = mul(x, x, mod);
        n >>= 1;
    }
    return ans;
}

// prime factorize
void factor(ll x)
{
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            cout << i << " ";
            while (n % i == 0)
            {
                n /= i;
            }
        }
    }
    if (n > 1)
    {
        cout << n;
    }
}

// arr has distinct positive integers, consider the following graph:
// n nodes, edge exists between arr[i] and arr[j] if and only if arr[i] and arr[j] share a common factor greater than 1, return the largest connected component.
ll factors[100001];
ll root[20001], size[20001];
ll n;
void init()
{
    for (ll i = 0; i < n; i++)
    {
        root[i] = i, size[i] = 1;
    }
    memset(factors, -1, sizeof(factors));
}
ll find(ll x)
{
    return root[x] != x ? root[x] = find(root[x]) : x;
}
void un(ll x, ll y)
{
    ll fx = find(x), fy = find(y);
    if (fx != fy)
    {
        root[fy] = fx;
        size[fx] += size[fy];
    }
}
ll max_size()
{
    ll ans = 0;
    for (ll i = 0; i < n; i++)
    {
        ans = max(ans, size[i]);
    }
    return ans;
}

ll larg_compon(vector<ll> &arr)
{
    n = arr.size();
    init();
    for (ll i = 0; i < n; i++)
    {
        ll x = arr[i];
        for (ll j = 2; j * j <= x; j++)
        {
            if (x % j == 0)
            {
                if (factors[j] == -1)
                {
                    factors[j] = i;
                }
                else
                {
                    un(i, factors[j]);
                }

                while (x % j == 0)
                {
                    x /= j;
                }
            }
        }
        if (x > 1)
        {
            if (factors[x] == -1)
            {
                factors[x] = i;
            }
            else
            {
                un(i, factors[x]);
            }
        }
    }
    return max_size();
}

// n * log(logn)
bool prime[10000001];
ll ehrlich(ll n)
{
    memset(prime, false, sizeof(prime)); // all prime
    for (ll i = 2; i * i <= n; i++)
    {
        if (!prime[i])
        {
            for (ll j = i * i; j <= n; j += i)
            {
                prime[j] = true;
            }
        }
    }
    ll cnt = 0;
    for (ll i = 2; i <= n; i++)
    {
        if (!prime[i])
        {
            cnt++;
        }
    }
    return cnt;

    vvl pfac(n + 1);
    for (ll i = 2; i <= n; i++)
    {
        if (!pfac[i].empty())
            continue;

        for (ll j = i; j <= n; j += i)
            pfac[j].push_back(i);
    }
    // vp(pfac[12]);
}

// n
bool vis[1001];
ll prime[501];
ll euler(ll n)
{
    memset(vis, false, sizeof(vis));
    ll cnt = 0;
    for (ll i = 2; i <= n; i++)
    {
        if (!vis[i])
        {
            prime[cnt++] = i;
        }
        for (ll j = 0; j < cnt; j++)
        {
            if (i * prime[j] > n)
            {
                break;
            }
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                break;
            }
        }
    }
    return cnt;
}