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

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--)
    {
        ll n, cnt = 0;
        cin >> n;
        vl arr(n + 1, 0), vis(n + 1, 0), pos(n, 0);

        for (ll i = 1; i <= n; i++)
        {
            cin >> arr[i];
            vis[arr[i]] = 1;
            if (arr[i] == 0)
            {
                pos[cnt++] = i;
            }
        }

        if (cnt == 1)
        {
            ll mis;
            for (ll i = 1; i <= n; i++)
            {
                if (vis[i] == 0)
                {
                    mis = i;
                }
            }
            arr[pos[0]] = mis;
        }
        ll l = 1, r = n;
        while (arr[l] == l || arr[r] == r)
        {
            arr[l] != l ?: l++;
            if (l >= r)
                break;
            arr[r] != r ?: r--;
        }
        if (l >= r)
            cout << 0 << endl;
        else
            cout << r - l + 1 << endl;
    }
}