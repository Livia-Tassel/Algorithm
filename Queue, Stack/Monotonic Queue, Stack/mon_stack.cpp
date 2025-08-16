#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <cstdlib>
#include <map>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;

// number smaller than it that is closest to it (without repeat).
vector<vector<ll>> mon_stack(const vector<ll> &arr)
{
    ll n = arr.size(), top = 0;
    vector<vector<ll>> ans(n, vector<ll>(2));
    ll s[n + 1];
    s[0] = -1; // top = 0, empty

    for (ll i = 0; i < n; i++)
    {
        while (top > 0 && arr[i] < arr[s[top]])
        {
            ll t = s[top--];
            ans[t][1] = i;
            ans[t][0] = s[top];
        }
        s[++top] = i;
    }

    while (top > 0)
    {
        ll t = s[top--];
        ans[t][1] = -1;
        ans[t][0] = s[top];
    }

    return ans;
}

// number smaller than it that is closest to it (repeat).
vector<vector<ll>> mon_stack_rep(const vector<ll> &arr)
{
    ll n = arr.size(), top = 0;
    vector<vector<ll>> ans(n, vector<ll>(2));
    ll s[n + 1];
    s[0] = -1; // top = 0, empty

    for (ll i = 0; i < n; i++)
    {
        while (top > 0 && arr[i] <= arr[s[top]])
        {
            ll t = s[top--];
            ans[t][1] = i;
            ans[t][0] = s[top];
        }
        s[++top] = i;
    }

    while (top > 0)
    {
        ll t = s[top--];
        ans[t][1] = -1;
        ans[t][0] = s[top];
    }

    for (ll i = n - 2; i >= 0; i--)
    {
        if (ans[i][1] != -1 && arr[i] == arr[ans[i][1]])
        {
            ans[i][1] = ans[ans[i][1]][1];
        }
    }

    return ans;
}

// sum of minimums of all subarrays
ll sum_min(const vector<ll> &arr)
{
    ll res = 0;
    ll n = arr.size(), top = 0;
    // this problem essentially doesn't require an ans array; only two variables are needed.
    vector<vector<ll>> ans(n, vector<ll>(2));
    ll s[n + 1];
    s[0] = -1; // top = 0, empty

    for (ll i = 0; i < n; i++)
    {
        while (top > 0 && arr[i] <= arr[s[top]])
        {
            ll t = s[top--];
            ans[t][1] = i;
            ans[t][0] = s[top];

            // when the element is popped from a monotonic stack, calculate the answer in which the current object participates, subsequently, this object no longer participates in the process of solving for future answers.
            res = (res + (t - ans[t][0]) * (ans[t][1] - t) * arr[t]) % mod;
            // ans = max(ans, height[t] * (ans[t][1] - ans[t][0] -1))
        }
        s[++top] = i;
    }

    while (top > 0)
    {
        ll t = s[top--];
        ans[t][1] = -1;
        ans[t][0] = s[top];

        res = (res + (t - ans[t][0]) * (n - t) * arr[t]) % mod;
        // ans = max(ans, height[t] * (n - ans[t][0] -1))
    }

    // for (ll i = n - 2; i >= 0; i--)
    // {
    //     if (ans[i][1] != -1 && arr[i] == arr[ans[i][1]])
    //     {
    //         ans[i][1] = ans[ans[i][1]][1];
    //     }
    // }

    return res;
}

signed main()
{
    vector<ll> arr = {3, 1, 4, 5, 2};
    ll result = sum_min(arr);

    cout << "Array: {3, 6, 1, 3, 4, 5, 3, 2, 7, 4, 5}" << endl;
    cout << "Indices: 0  1  2  3  4  5  6  7  8  9  10" << endl;
    cout << "-------------------------------" << endl;

    cout << result << endl;

    // for (ll i = 0; i < arr.size(); i++)
    // {
    //     cout << "Element " << arr[i] << " at Index " << i << ":" << endl;
    //     cout << "  Left Smaller: " << Result[i][0] << endl;
    //     cout << "  Right Smaller: " << Result[i][1] << endl;
    // }

    return 0;
}