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

ll solve(ll n)
{
    ll neg = 0, pos = 0, ans = 0, a;
    for (ll i = 0; i < n; i++)
    {
        cin >> a;
        if (a < 0)
            neg++;
        else if (a > 0)
            pos++;
        else
            ans++;
    }
    neg %= 2;
    return ans + 2 * neg;
}
signed main()
{
    ll t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        cout << solve(n) << endl;
    }
}