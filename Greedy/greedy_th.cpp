#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <climits>
#include <set>
#define ll long long
using namespace std;

// arr positive integers, you can divide even numbers by 2 or multiply odd numbers by 2, find the minimum possible maximum difference between any two elements after some operations.
ll deviation(vector<ll> &nums)
{
    set<ll> s;
    for (ll num : nums)
    {
        s.insert(num % 2 != 0 ? 2 * num : num);
    }

    ll ans = *s.rbegin() - *s.begin();
    while (ans > 0 && *s.rbegin() % 2 == 0)
    {
        ll max = *s.rbegin();
        s.erase(max);
        max /= 2;
        s.insert(max);
        ans = min(ans, *s.rbegin() - *s.begin());
    }

    return ans;
}

// array answers containing replies from several rabbits to the question, "how many other rabbits are the same color as you?", find the minimum number of rabbits in the forest.
ll rabbits(vector<ll> &answers)
{
    unordered_map<ll, ll> mp;
    ll ans = 0;
    for (ll aw : answers)
    {
        mp[aw]++;
    }
    for (auto &rb : mp)
    {
        // cell(a/b) = (a + b - 1)/b
        ans += (rb.second + rb.first) / (rb.first + 1) * (rb.first + 1);
    }
    return ans;
}

// arrays nums and target, you can perform an operation: choose two distinct i and j in nums and set nums[i] += 2, nums[j] -= 2, find the minimum number of operations to make nums and target similar (i.e., have the same element frequencies).
ll split(vector<ll> &arr, ll n)
{
    ll osize = 0;
    for (ll i = 0; i < n; i++)
    {
        if (arr[i] & 1)
        {
            swap(arr[i], arr[osize++]);
        }
    }
    return osize;
}
ll similar(vector<ll> &nums, vector<ll> &tar)
{
    ll n = tar.size();
    ll osize = split(tar, n);
    sort(tar.begin(), tar.begin() + osize);
    sort(tar.begin() + osize, tar.end());
    split(nums, n);
    sort(nums.begin(), nums.begin() + osize);
    sort(nums.begin() + osize, nums.end());

    ll ans = 0;
    for (ll i = 0; i < n; i++)
    {
        ans += abs(nums[i] - tar[i]);
    }
    return ans / 4;
}

// n employees, each with two ability scores a_i and b_i, when two employees i, j form a team, their team abilities are x = (a_i+a_j)/2 and y = (b_i+b_j)/2, maximize(min(X, Y)).
double quiz(vector<vector<ll>> &abt)
{
    sort(abt.begin(), abt.end(), [](const vector<ll> &a, const vector<ll> &b)
         { return abs(a[0] - a[1]) < abs(b[0] - b[1]); });

    ll n = abt.size();
    ll amax = abt[0][0], bmax = abt[0][1];
    ll ans = 0;
    for (ll i = 1; i < n; i++)
    {
        if (abt[i][0] > abt[i][1])
        {
            ans = max(ans, abt[i][1] + bmax);
        }
        else
        {
            ans = max(ans, abt[i][0] + amax);
        }
        amax = max(amax, abt[i][0]), bmax = max(bmax, abt[i][1]);
    }
    return ans / 2.0;
}

// sorted array, determine if arr can be partitioned into one or more non-overlapping, increasing subsequences, each of length at least k.
bool partition(vector<ll> &arr, ll k)
{
    // approach: the more subsequences you have, the harder it is to reach the goal, therefore, using the frequency of the most frequent number as the number of subsequences is optimal.
    // 1 1 2 2 3 3 3 4 4 5 6 7
    // 1 2 3 5
    //   2 3 4 7
    //   1 3 4 6
    ll cnt = 1, max = 1;
    ll n = arr.size();
    for (ll i = 1; i < n; i++)
    {
        if (arr[i] != arr[i - 1])
        {
            max = std::max(max, cnt);
            cnt = 1;
        }
        else
        {
            cnt++;
        }
    }
    max = std::max(max, cnt);
    return n / max >= k;
}