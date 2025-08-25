#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <climits>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;

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

// length bamboo_len, cut it into several pieces of positive integer length, find the maximum product of the lengths of these pieces.
ll bamboo(ll len)
{
    if (len < 4)
    {
        return len - 1;
    }
    // n = 4   →  2 2
    // n = 5   →  3 2
    // n = 6   →  3 3
    // n = 7   →  3 2 2
    // n = 8   →  3 3 2
    // n = 9   →  3 3 3
    // n = 10  →  3 3 2 2
    // n = 11  →  3 3 3 2
    ll tail = (len % 3 != 0 ? (len % 3 != 1 ? 2 : 4) : 1);
    ll p = (tail != 1 ? (len - tail) : len) / 3;

    return (qpow(3, p, mod) * tail % mod);
}

// n must be partitioned into k parts, find the maximum possible product of these parts; n, k up to 10^12.
ll f(ll rest, ll k)
{
    if (k == 1)
    {
        return rest;
    }
    ll ans = LLONG_MIN;
    for (ll cur = 1; cur - 1 < rest && (rest - cur) >= (k - 1); cur++)
    {
        ll curAns = cur * f(rest - cur, k - 1);
        ans = max(ans, curAns);
    }
    return ans;
}

ll bao(ll n, ll k)
{
    return f(n, k);
}

ll bea(ll n, ll k)
{
    ll a = n / k;
    ll b = n % k;
    return (ll)((qpow(a + 1, b, mod) * qpow(a, k - b, mod)) % mod);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    random_device rd;
    mt19937 gen(rd());

    ll N = 30;
    ll times = 2001;
    cout << "Test Start!" << endl;
    for (int i = 1; i < times; i++)
    {
        uniform_int_distribution<> n_dist(1, N);
        ll n = n_dist(gen);
        uniform_int_distribution<> k_dist(1, n);
        ll k = k_dist(gen);

        if (bao(n, k) != bea(n, k))
        {
            cout << "error!" << endl;
            // cout << "n = " << n << ", k = " << k << endl;
            // cout << "bao(n, k) = " << bao(n, k) << ", bea(n, k) = " << bea(n, k) << endl;
            break;
        }
    }
    cout << "Test Over!" << endl;

    return 0;
}

// maximum event selection problem, sorting events by their end times.
ll f(vector<vector<ll>> &mt, ll n, ll i)
{
    ll ans = 0;
    if (i != n)
    {
        for (ll j = i; j < n; j++)
        {
            swap(mt[i], mt[j]);
            ans = max(ans, f(mt, n, i + 1));
            swap(mt[i], mt[j]);
        }
    }
    else
    {
        ll curAns = 0;
        ll curTime = -1;
        for (ll j = 0; j < n; j++)
        {
            if (curTime <= mt[j][0])
            {
                curAns++;
                curTime = mt[j][1];
            }
        }
        ans = curAns;
    }
    return ans;
}
ll bao(vector<vector<ll>> &mt)
{
    return f(mt, mt.size(), 0);
}

ll meeting(vector<vector<ll>> &mt)
{
    sort(mt.begin(), mt.end(), [](const vector<ll> &a, const vector<ll> &b)
         { return a[1] < b[1]; });

    ll ans = 0, n = mt.size();
    for (ll i = 0, time = -1; i < n; i++)
    {
        if (time <= mt[i][0])
        {
            ans++;
            time = mt[i][1];
        }
    }
    return ans;
}

// maximum event selection problem, but each event requires one day to attend, and you can only attend one event per day.
ll events(vector<vector<ll>> &events)
{
    sort(events.begin(), events.end(), [](const vector<ll> &a, const vector<ll> &b)
         { return a[0] < b[0]; });
    priority_queue<ll, vector<ll>, greater<ll>> pq;

    ll min = events[0][0];
    ll max = 0;
    for (vector<ll> &eve : events)
    {
        max = std::max(max, eve[1]);
    }

    ll ans = 0, pos = 0;
    ll n = events.size();
    for (ll i = min; i <= max; i++)
    {
        while (pos < n && i == events[pos][0])
        {
            pq.push(events[pos++][1]);
        }
        while (!pq.empty() && pq.top() < i)
        {
            pq.pop();
        }

        if (!pq.empty())
        {
            ans++;
            pq.pop();
        }
    }

    return ans;
}

// non-negative arr, repeatedly calculate the absolute difference of any two numbers and add any new differences to arr, return the final length of arr when its size no longer changes.
ll gcd(ll a, ll b)
{
    return b != 0 ? gcd(b, a % b) : a;
}
ll abs_diff(vector<ll> &arr)
{
    ll max = 0, all_gcd = 0;
    for (ll num : arr)
    {
        if (num != 0)
        {
            all_gcd = num;
        }
        max = std::max(max, num);
    }

    if (!all_gcd)
    {
        return arr.size();
    }

    unordered_map<ll, ll> mp;
    for (ll num : arr)
    {
        mp[num]++;
        if (num != 0)
        {
            all_gcd = gcd(all_gcd, num);
        }
    }
    ll ans = max / all_gcd;
    bool rep = false;
    for (auto itr : mp)
    {
        if (itr.first != 0)
        {
            ans += (itr.second - 1);
            if (itr.second > 1)
            {
                rep = true;
            }
        }
    }

    if (mp[0] > 0)
    {
        ans += mp[0];
    }
    else if (rep)
    {
        ans++;
    }

    return ans;
}
