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
const ll maxn = 1001;
vl arr(maxn);

void solve(ll n)
{
    for (ll i = 1; i < n + 1; i++)
    {
        cin >> arr[i];
    }
    vl sum(n + 1, 0);
    sum[1] = arr[1];
    for (ll i = 2; i < n + 1; i++)
    {
        sum[i] = sum[i - 1] + arr[i];
    }

    for (ll l = 1; l < n; l++)
    {
        for (ll r = l + 1; r < n; r++)
        {
            ll s1 = sum[l] % 3;
            ll s2 = (sum[r] - sum[l]) % 3;
            ll s3 = (sum[n] - sum[r]) % 3;
            if ((s1 == s2 && s2 == s3) || (s1 != s2 && s2 != s3 && s1 != s3))
            {
                cout << l << " " << r << endl;
                return;
            }
        }
    }
    cout << 0 << " " << 0 << endl;
}
signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        solve(n);
    }
}