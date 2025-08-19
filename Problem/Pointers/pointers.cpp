#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#define ll long long
using namespace std;
const ll MAXN = 1001;

void print_vector(const vector<ll> &arr)
{
    for (ll val : arr)
    {
        cout << val << " ";
    }
    cout << endl;
}

// rearrange an array such that odd numbers are placed at odd indices and even numbers are placed at even indices.
void rearrange(vector<ll> &arr)
{
    ll n = arr.size(), even = 0, odd = 1;

    while (even < n && odd < n)
    {
        if (arr[n - 1] % 2 != 0)
        {
            swap(arr[odd], arr[n - 1]);
            odd += 2;
        }
        else
        {
            swap(arr[even], arr[n - 1]);
            even += 2;
        }
    }
}

// arr length n+1, range 1 to n, where only one number is repeated, return the repeated number.
ll rep_num(vector<ll> &arr)
{
    if (arr.size() < 2)
    {
        return -1;
    }
    ll fast = arr[arr[0]], slow = arr[0];

    while (fast != slow)
    {
        fast = arr[arr[fast]];
        slow = arr[slow];
    }

    fast = 0;
    while (fast != slow)
    {
        fast = arr[fast];
        slow = arr[slow];
    }

    return fast;
}

// histogram water collection problem, how much water can be trapped at most?
// ll trap(vector<ll> &height)
// {
//     ll ans = 0, lm, rm, n = height.size();
//     ll left[n], right[n];
//     left[0] = height[0];
//     for (ll i = 1; i < n; i++)
//     {
//         left[i] = max(height[i], left[i - 1]);
//     }
//     right[n - 1] = height[n - 1];
//     for (ll i = n - 2; i >= 0; i--)
//     {
//         right[i] = max(height[i], right[i + 1]);
//     }

//     for (ll i = 1; i < n - 1; i++)
//     {
//         lm = left[i - 1], rm = right[i + 1];
//         ans += max(min(lm, rm) - height[i], (ll)0);
//     }

//     return ans;
// }
ll trap(vector<ll> &height)
{
    ll ans = 0, n = height.size();
    ll lm = height[0], rm = height[n - 1], l = 1, r = n - 2;

    while (l <= r)
    {
        if (lm >= rm)
        {
            ans += max(rm - height[r], (ll)0);
            rm = max(height[r--], rm);
        }
        else
        {
            ans += max(lm - height[l], (ll)0);
            lm = max(height[l++], lm);
        }
    }

    return ans;
}

// n people crossing a river (all with weights not exceeding limit), each boat can hold at most two people and has a weight limit, return the minimum number of boats needed?
ll rescue(vector<ll> &peo, ll limit)
{
    ll n = peo.size(), ans = 0;
    ll l = 0, r = n - 1;
    sort(peo.begin(), peo.end());

    while (l <= r)
    {
        peo[r--] + peo[l] > limit ?: l++;
        ans++;
    }

    return ans;
}

// among lots of lines, choose two lines that can trap the most water.
ll area(vector<ll> &high)
{
    ll n = high.size(), ans = 0;
    ll l = 0, r = n - 1;

    while (l < r)
    {
        ans = max(ans, (r - l) * min(high[l], high[r]));
        // Ingeniously Superb
        high[l] < high[r] ? l++ : r--;
    }

    return ans;
}

// the minimum heating radius required to cover all houses.
ll radius(vector<ll> &hou, vector<ll> &heat)
{
    // each house find its nearest heater, then find the maximum of all these distances.
    sort(hou.begin(), hou.end());
    sort(heat.begin(), heat.end());
    ll pu = 0, pt = 0, ans = 0;
    ll n = hou.size(), m = heat.size();

    while (pu < n)
    {
        while (pt < m - 1 && abs(hou[pu] - heat[pt]) >= abs(hou[pu] - heat[pt + 1]))
        {
            pt++;
        }
        ans = max(ans, (ll)abs(hou[pu++] - heat[pt]));
    }

    return ans;
}

// the first missing positive integer in an unsorted array.
ll mis_pos(vector<ll> &arr)
{
    // right side of r is the garbage area (including r), and the left side of l is the completed area (not including l).
    ll n = arr.size();
    ll l = 0, r = n;

    while (l < r)
    {
        if (arr[l] == l + 1)
        {
            l++;
            continue;
        }

        if (arr[l] < l + 1 || arr[l] > r || arr[arr[l] - 1] == arr[l])
        {
            swap(arr[l], arr[--r]);
            continue;
        }

        swap(arr[l], arr[arr[l] - 1]);
    }

    return l + 1;
}

signed main()
{

    return 0;
}