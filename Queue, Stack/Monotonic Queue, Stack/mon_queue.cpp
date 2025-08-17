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

// monotonic queue to maintain maximum and minimum in a sliding window.
vector<ll> max_slid(const vector<ll> &arr, ll k)
{
    ll n = arr.size(), h = 0, t = 0;
    ll dq[n]; // [h, t)

    for (ll i = 0; i < k - 1; i++)
    {
        while (h < t && arr[i] >= arr[dq[t - 1]])
        {
            t--;
        }
        dq[t++] = i;
    }

    vector<ll> ans;
    for (ll l = 0, r = k - 1; r < n; l++, r++)
    {
        while (h < t && arr[r] >= arr[dq[t - 1]])
        {
            t--;
        }
        dq[t++] = r;

        ans.push_back(arr[dq[h]]);
        // l is about to slide away, check if the head of the monotonic queue has expired.
        dq[h] != l ? h : h++;
    }

    return ans;
}

// longest subarray where the difference between its maximum and minimum elements is less than or equal to limit.
const ll MAXN = 100005;
ll dq_max[MAXN], dq_min[MAXN];
ll hx = 0, tx = 0, hn = 0, tn = 0;
bool ok(const vector<ll> &arr, ll limit, ll num)
{
    ll max = hx < tx ? std::max(arr[dq_max[hx]], num) : num;
    ll min = hn < tn ? std::min(arr[dq_min[hn]], num) : num;
    return (max - min) > limit ? false : true;
}
ll long_sub(const vector<ll> &arr, ll limit)
{
    ll n = arr.size(), ans = 0;

    for (ll l = 0, r = 0; l < n; l++)
    {
        while (r < n && ok(arr, limit, arr[r]))
        {
            while (hx < tx && arr[r] >= arr[dq_max[tx - 1]])
            {
                tx--;
            }
            dq_max[tx++] = r;

            while (hn < tn && arr[r] <= arr[dq_min[tn - 1]])
            {
                tn--;
            }
            dq_min[tn++] = r;

            r++;
        }
        ans = std::max(ans, r - l);

        (hx < tx && dq_max[hx] == l) ? hx++ : hx;
        (hn < tn && dq_min[hn] == l) ? hn++ : hn;
    }

    return ans;
}