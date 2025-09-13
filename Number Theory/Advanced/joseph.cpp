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
using vvl = vector<vector<ll>>;
using vvd = vector<vector<double>>;
using vd = vector<double>;
using vl = vector<ll>;
const ll mod = 1e9 + 7;
const ll maxn = 10001;

ll compute(ll n, ll k)
{
    ll ans = 1;
    for (ll c = 2; c < n + 1; c++)
    {
        ans = (ans + k - 1) % c + 1;
    }
    return ans;
}

// k → arr[i]
ll joseph(ll n, vl &arr)
{
    if (n == 1)
    {
        return 1;
    }
    ll ans = 1;
    for (ll c = 2, i = n - 1; c < n + 1; c++, i--)
    {
        ans = (ans + arr[i] - 1) % c + 1;
    }
    return ans;
}