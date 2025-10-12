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

bool is_prime(ll n)
{
    if (n <= 1)
    {
        return false;
    }
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}
void solve()
{
    ll n, k;
    cin >> n >> k;
    if ((is_prime(n) && k == 1) || (n == 1 && k == 2))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}
signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}