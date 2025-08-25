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
const ll mod = 1e9 + 7;

// array, you can sort a contiguous subarray to make the entire array becomes sorted in ascending order, find the shortest subarray length.
ll unsorted(vector<ll> &nums)
{
    // 1 2 5 4 3 6 7
    // √ √ √ × × √ √
    // √ √ × × √ √ √
    ll n = nums.size();
    ll max = LLONG_MIN, min = LLONG_MAX;
    ll r = -1;
    for (ll i = 0; i < n; i++)
    {
        max = std::max(max, nums[i]);
        if (nums[i] < max)
        {
            r = i;
        }
    }
    ll l = n;
    for (ll i = n - 1; i >= 0; i--)
    {
        min = std::min(min, nums[i]);
        if (nums[i] > min)
        {
            l = i;
        }
    }

    return std::max(r - l + 1, (ll)0);
}

// k non-decreasingly sorted lists of integers, find the minimum interval that includes at least one number from each of the k lists.
struct node
{
    ll v;
    ll k;
    ll pos;
    node(ll val, ll i, ll j) : v(val), k(i), pos(j) {}
    bool operator<(const node &other) const
    {
        if (v != other.v)
        {
            return v < other.v;
        }
        return k < other.k;
    }
};

vector<ll> smallest(vector<vector<ll>> &nums)
{
    ll n = nums.size();
    set<node> sma;
    for (ll i = 0; i < n; i++)
    {
        sma.insert(node(nums[i][0], i, 0));
    }

    ll ans = LLONG_MAX;
    ll l = 0, r = 0;
    while (sma.size() > n - 1)
    {
        node min = *sma.begin(), max = *sma.rbegin();
        sma.erase(sma.begin());

        if (max.v - min.v < ans)
        {
            ans = max.v - min.v;
            l = min.v, r = max.v;
        }

        ll i = min.k, j = min.pos;
        if (j + 1 < nums[i].size())
        {
            sma.insert(node(nums[i][j + 1], i, j + 1));
        }
    }

    vector<ll> res = {l, r};
    return res;
}

// n people can choose from m activities or play nothing at all，the total cost for activity i is C_i​(X) = max(X (B_i − K_iX),0), where X is the number of participants, find the maximum possible total cost when all n people make their choices.
struct park
{
    ll ki;
    ll bi;
    ll peo;

    park(ll k, ll b) : ki(k), bi(b), peo(0) {}
    ll earn() const
    {
        // one more people
        // (peo+1).(bi-(peo+1).ki) - peo.(bi-peo.ki)
        return bi - (2 * peo + 1) * ki;
    }
};
struct comp
{
    bool operator()(const park &a, const park &b) const
    {
        return a.earn() < b.earn();
    }
};

ll cost_max(ll n, vector<vector<ll>> &active)
{
    ll m = active.size();
    priority_queue<park, vector<park>, comp> pq;

    for (vector<ll> &act : active)
    {
        pq.push(park(act[0], act[1]));
    }

    ll ans = 0;
    for (ll i = 0; i < n; i++)
    {
        park cur = pq.top();
        pq.pop();
        if (cur.earn() >= 0)
        {
            ans += cur.earn();
            cur.peo++;
            pq.push(cur);
        }
        else
        {
            break;
        }
    }

    return ans;
}

// arr length n, you must partition arr into exactly k subsets, return the minimum possible sum of the average values of each subset.
ll ave_sum(vector<ll> &arr, ll k)
{
    sort(arr.begin(), arr.end());
    ll ans = 0;
    for (ll i = 0; i < k - 1; i++)
    {
        ans += arr[i];
    }
    ll aver = 0, n = arr.size();
    for (ll i = k - 1; i < n; i++)
    {
        aver += arr[i];
    }
    aver /= n - k + 1;
    return ans + aver;
}

// tasks, each with an energy cost and a minimum starting energy, you can complete the tasks in any order, find the minimum initial energy required to complete all tasks.
ll effort(vector<vector<ll>> &tasks)
{
    // {cost - starting}
    sort(tasks.begin(), tasks.end(), [](const vector<ll> &a, const vector<ll> &b)
         { return a[0] - a[1] > b[0] - b[1]; });

    ll ans = 0;
    for (vector<ll> &tk : tasks)
    {
        ans = max(ans + tk[0], tk[1]);
    }
    return ans;
}