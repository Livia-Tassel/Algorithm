#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#define endl '\n'
using namespace std;
using ll = long long;

void solve()
{
    int n;
    ll k;
    cin >> n >> k;
    map<ll, int> cnt;

    // (x + k) % k === x % k
    // if x >= k, |x - k| = x - k, then (x - k) % k === x % k
    // if x < k, |x - k| = k - x, then (k - x) % k === -x % k
    for (int i = 0; i < n; ++i)
    {
        ll s;
        cin >> s;
        ll r = s % k;
        ll key = min(r, (k - r) % k);
        cnt[key]++;
    }

    for (int i = 0; i < n; ++i)
    {
        ll t;
        cin >> t;
        ll r = t % k;
        ll key = min(r, (k - r) % k);
        cnt[key]--;
    }

    bool flag = true;
    for (auto const &[key, val] : cnt)
    {
        if (val != 0)
        {
            flag = false;
            break;
        }
    }

    cout << (flag ? "YES" : "NO") << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}