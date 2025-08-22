#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <unordered_set>
#include <deque>
#define ll long long
using namespace std;

// using words from a word list as bridges, starting from ben, change one character at a time to become end, return the length of one shortest path.
unordered_set<string> lar_level, sma_level, next_level;
unordered_map<string, vector<string>> g;

ll bfs(unordered_set<string> &dict, string beg, string end)
{
    sma_level.insert(beg);
    lar_level.insert(end);

    ll len = 2;
    while (!sma_level.empty())
    {
        for (string s : sma_level)
        {
            for (ll i = 0; i < s.length(); i++)
            {
                char old = s[i];
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    string str = s;
                    str[i] = ch;
                    if (str != s)
                    {
                        if (lar_level.count(str))
                        {
                            return len;
                        }
                        if (dict.count(str))
                        {
                            dict.erase(str);
                            next_level.insert(str);
                        }
                    }
                }
            }
        }
        len++;
        if (lar_level.size() < next_level.size())
        {
            sma_level = lar_level;
            lar_level = next_level;
        }
        else
        {
            sma_level = next_level;
        }
        next_level.clear();
    }

    return 0;
}
ll ladders(string beg, string end, vector<string> &list)
{
    unordered_set<string> dict(list.begin(), list.end());

    if (!dict.count(end))
    {
        return 0;
    }

    return bfs(dict, beg, end);
}

// n items with sizes v[i] and a backpack with capacity w, return the number of subsets of items whose total size does not exceed w (including the subset with a total size of 0)
ll n, w;
vector<ll> arr(40), lsum(1 << 20), rsum(1 << 20);
ll f(ll s, ll e, ll pak, ll w, vector<ll> &ans, ll pos)
{
    if (pak > w)
    {
        return pos;
    }

    if (s != e)
    {
        pos = f(s + 1, e, pak, w, ans, pos);
        pos = f(s + 1, e, pak + arr[s], w, ans, pos);
    }
    else
    {
        ans[pos++] = pak;
    }

    return pos;
}

ll compute()
{
    // n = 30, and v[i] = 10^9 is so large that dynamic programming is not feasible, we can split the items llo two halves, brute-force all subsets for each half, and then combine the results.
    ll lsize = f(0, n >> 1, 0, w, lsum, 0); // [0, n/2)
    ll rsize = f(n >> 1, n, 0, w, rsum, 0); // [n/2, n)

    sort(lsum.begin(), lsum.begin() + lsize);
    sort(rsum.begin(), rsum.begin() + rsize);

    ll ans = 0;
    for (ll i = lsize - 1, j = 0; i >= 0; i--)
    {
        while (j < rsize && lsum[i] + rsum[j] - 1 < w)
        {
            j++;
        }
        ans += j;
    }
    return ans;
}

// get a subsequence whose sum minimizes abs(sum - goal), return this minimum absolute difference.
ll pos;
vector<ll> lsum, rsum;
void f(ll s, ll e, ll sum, vector<ll> &ans, vector<ll> &nums)
{
    if (s != e)
    {
        ll ns = s + 1;
        while (ns < e && nums[s] == nums[ns])
        {
            ns++;
        }

        for (ll k = 0; k < ns - s + 1; k++)
        {
            f(ns, e, sum + k * nums[s], ans, nums);
        }
    }
    else
    {
        ans[pos++] = sum;
    }
}
ll min_abs(vector<ll> &nums, ll goal)
{
    ll n = nums.size();

    ll min_sum = 0, max_sum = 0;
    for (ll x : nums)
    {
        x > 0 ? max_sum += x : min_sum += x;
    }
    if (max_sum < goal)
        return (ll)(goal - max_sum);
    if (min_sum > goal)
        return (ll)(min_sum - goal);

    ll left_n = n / 2;
    ll right_n = n - left_n;
    lsum.resize(1 << left_n);
    rsum.resize(1 << right_n);

    sort(nums.begin(), nums.end());

    pos = 0;
    f(0, left_n, 0, lsum, nums);
    ll lsize = pos;

    pos = 0;
    f(left_n, n, 0, rsum, nums);
    ll rsize = pos;

    sort(lsum.begin(), lsum.begin() + lsize);
    sort(rsum.begin(), rsum.begin() + rsize);

    ll ans = abs(goal);
    for (ll i = 0, j = rsize - 1; i < lsize; i++)
    {
        while (j > 0 && abs(goal - lsum[i] - rsum[j]) >= abs(goal - lsum[i] - rsum[j - 1]))
        {
            j--;
        }
        ans = std::min(ans, abs(goal - lsum[i] - rsum[j]));
    }
    return ans;
}
