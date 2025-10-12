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
    ll n, q;
    cin >> n >> q;
    ll arr[n + 1];
    vl idx(n + 1, 0);
    for (ll i = 1; i <= n; i++)
    {
        cin >> arr[i];
        idx[arr[i]] = i;
    }
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        ll k;
        cin >> k;
        if (idx[k] > r || idx[k] < l)
        {
            cout << -1 << " ";
            continue;
        }

        // total number of digits greater than k and less than k in the permutation
        ll big = n - k, sml = k - 1;
        // cumulative number of "bad points"
        ll nBig = 0, nSml = 0;
        // remaining number of digits greater than k and less than k for exchange
        ll bigAv = n - k, smlAv = k - 1;
        ll lo = l, hi = r;
        while (lo <= hi)
        {
            ll mid = (lo + hi) / 2;
            if (arr[mid] == k)
                break;

            // target on the right
            if (mid < idx[k])
            {
                if (k < arr[mid])
                {
                    nSml++;
                }
                else
                {
                    smlAv--;
                }
                sml--;
                lo = mid + 1;
            }
            else
            {
                if (k > arr[mid])
                {
                    nBig++;
                }
                else
                {
                    bigAv--;
                }
                big--;
                hi = mid - 1;
            }
        }
        if (big < 0 || sml < 0)
        {
            cout << -1 << " ";
            continue;
        }
        ll ans = 2 * min(nBig, nSml);
        ll diff = abs(nBig - nSml);
        if (nBig > nSml)
        {
            if (bigAv < diff)
                cout << -1 << " ";
            else
                cout << ans + 2 * diff << " ";
        }
        else
        {
            if (smlAv < diff)
                cout << -1 << " ";
            else
                cout << ans + 2 * diff << " ";
        }
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