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
const ll maxn = 2e5 + 5;

vl a(maxn);
bool solve(ll n, ll k)
{
    string s;
    cin >> s;
    ll cnt = 0;
    for (char ch : s)
    {
        if (ch == '1')
            cnt++;
    }
    if (k >= cnt)
        return true;
    // k > n - k
    return 2 * k > n;
}
signed main()
{
    ll t, n, k;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        cout << (solve(n, k) ? "Alice" : "Bob") << endl;
    }
}