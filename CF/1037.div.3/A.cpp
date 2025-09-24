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
    ll ans = 10;
    while (n > 0)
    {
        ans = min(ans, n % 10);
        n /= 10;
    }
    return ans;
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