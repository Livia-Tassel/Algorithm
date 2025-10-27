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

void solve()
{
    ll n;
    cin >> n;
    map<ll, ll> cnt;
    for (ll i = 0, c; i < n; i++)
    {
        cin >> c;
        cnt[c]++;
    }
    ll sum = 0, top = 1, eg = 0;
    vl re(n + 1, 0);
    for (auto &p : cnt)
    {
        sum += (p.first * 2 * (p.second / 2));
        eg += 2 * (p.second / 2);
        if (p.second % 2 == 1)
        {
            re[top++] = p.first;
        }
    }
    sort(re.begin() + 1, re.begin() + top);
    for (ll i = top - 1; i > 0; i--)
    {
        if (sum + re[i - 1] > re[i])
        {
            cout << sum + re[i - 1] + re[i] << endl;
            return;
        }
    }
    if (eg > 2)
    {
        cout << sum << endl;
    }
    else
    {
        cout << 0 << endl;
    }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}