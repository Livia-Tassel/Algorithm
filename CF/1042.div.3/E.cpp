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
const ll maxn = 200005;

vl a(maxn), b(maxn);
bool solve(ll n)
{
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    for (ll i = 1; i <= n; i++)
        cin >> b[i];

    if (a[n] != b[n])
        return false;

    for (ll i = n - 1; i > 0; i--)
    {
        if (a[i] != b[i] && (a[i] ^ a[i + 1]) != b[i] && (a[i] ^ b[i + 1]) != b[i])
            return false;
    }
    return true;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << (solve(n) ? "YES" : "NO") << endl;
    }
}

// a[i] = a[i] ^ a[i+1] <=> swap(pra[i], pra[i+1]), pra[i]=a[0]^a[1]^...^a[i]