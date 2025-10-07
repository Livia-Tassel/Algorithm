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
using namespace std;
using ll = long long;
using vl = vector<ll>;

void solve()
{
    int n;
    cin >> n;
    vl a(n), b(n);

    for (auto &it : a)
        cin >> it;
    for (auto &it : b)
        cin >> it;

    vl vis(n + 1);
    if (a.back() == b.back())
    {
        cout << n << endl;
        return;
    }

    int ans = -1;
    // for i, we can get all value of [i+2, n]
    for (int i = n - 2; i >= 0; i--)
    {
        if (a[i] == b[i] || a[i] == a[i + 1] || b[i] == b[i + 1] || vis[a[i]] || vis[b[i]])
        {
            ans = i;
            break;
        }

        vis[a[i + 1]] = vis[b[i + 1]] = true;
    }

    cout << ans + 1 << endl;
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
}