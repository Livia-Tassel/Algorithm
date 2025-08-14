#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#define ll long long
using namespace std;
const ll MAXN = 1001;
vector<ll> arr;
ll offset = 0; // avoid negative array position
void init(ll n)
{
    arr.assign(n + 3 + offset, 0);
}

// difference of an arithmetic progression
// [l, r] + {a + (n-1)*d}
void modify(ll l, ll r, ll s, ll e, ll d)
{
    // s d-s ... -d-e e
    // s  d  ...  -e  0
    // s s+d ...   0  0
    arr[l + offset] += s;
    arr[l + 1 + offset] += d - s;
    arr[r + 1 + offset] -= d + e;
    arr[r + 2 + offset] += e;
}

void build(ll n)
{
    for (ll i = 1; i <= n + offset; i++)
    {
        arr[i] += arr[i - 1];
    }
    for (ll i = 1; i <= n + offset; i++)
    {
        arr[i] += arr[i - 1];
    }
}

void print_arr(ll n, const string &title)
{
    for (ll i = 1 + offset; i <= n + offset; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

signed main()
{
    ll n = 10;
    return 0;
}