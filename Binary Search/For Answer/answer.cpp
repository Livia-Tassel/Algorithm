#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <climits>
#define ll long long
using namespace std;

// array length n, partition it into k contiguous subarrays, find the partition method that minimizes the maximum sum among all subarrays (arr[i] >= 0).
// ll f(const vector<ll> &arr, ll limit)
// {
//     ll k = 1, sum = 0;

//     for (ll num : arr)
//     {
//         if (num > limit)
//         {
//             return LLONG_MAX;
//         }

//         if (sum + num > limit)
//         {
//             k++;
//             sum = num;
//         }
//         else
//         {
//             sum += num;
//         }
//     }

//     return k;
// }
// ll par_min(const vector<ll> &arr, ll k)
// {
//     ll sum = 0, ans = 0;
//     for (ll num : arr)
//     {
//         sum += num;
//     }

//     ll l = 0, r = sum, m;
//     while (l <= r)
//     {
//         m = (l + r) / 2;
//         if (f(arr, m) <= k)
//         {
//             ans = m;
//             r = m - 1;
//         }
//         else
//         {
//             l = m + 1;
//         }
//     }

//     return ans;
// }

// the k-th smallest absolute difference between any two numbers.
// ll f(const vector<ll> &arr, ll limit)
// {
//     ll n = arr.size(), ans = 0;
//     for (ll l = 0, r = 0; l < n; l++)
//     {
//         while (r + 1 < n && arr[r + 1] - arr[l] <= limit)
//         {
//             r++;
//         }
//         ans += (r - l);
//     }

//     return ans;
// }
// ll sma_abs(vector<ll> &arr, ll k)
// {
//     ll n = arr.size(), ans;
//     sort(arr.begin(), arr.end());

//     ll l = 0, r = arr[n - 1] - arr[0], m;
//     while (l <= r)
//     {
//         // arr = {1, 3, 5, 8, 10}
//         // 2, 2, 2, 3, 4, 5, 5, 7, 7, 9
//         m = (l + r) / 2;
//         if (f(arr, m) >= k)
//         {
//             ans = m;
//             r = m - 1;
//         }
//         else
//         {
//             l = m + 1;
//         }
//     }

//     return ans;
// }

// battery pack powers n computers, return the maximum amount of time the n computers can run simultaneously (the battery switching speed is negligible).
bool f(const vector<ll> &batt, ll n, ll minute)
{
    // Conclusion 1: If a single battery's capacity is greater than minute, it can independently power one computer.

    // Conclusion 2 : The total capacity of the remaining "fragmented" batteries only needs to be greater than or equal to the number of remaining computers multiplied by minute.

    ll sum = 0;
    for (ll x : batt)
    {
        if (x > minute)
        {
            n--;
        }
        else
        {
            sum += x;
        }

        if (sum >= n * minute)
        {
            return true;
        }
    }

    return false;
}
ll max_cpu(const vector<ll> &batt, ll n)
{
    ll sum = 0, max = 0;
    for (ll x : batt)
    {
        sum += x;
        max = std::max(x, max);
    }

    if (sum > max * n)
    {
        return sum / n;
    }

    ll l = 0, r = max, m, ans = 0;
    while (l <= r)
    {
        m = (l + r) / 2;
        if (f(batt, n, m))
        {
            ans = m;
            l = m + 1;
        }
        else
        {
            r = m - 1;
        }
    }

    return ans;
}

// group of bath attendants, each with a fixed scrubbing time，assuming m people are waiting, and everyone follows the principle of taking an available spot as soon as it's free, what is the minimum waiting time?
ll f(const vector<ll> &bath, ll tim)
{
    ll sum = 0;
    for (ll ser : bath)
    {
        sum += (tim / ser + 1);
    }

    return sum;
}
ll min_bath(const vector<ll> &bath, ll m)
{
    // can be analyzed that if a person has multiple choices, the final answer is independent of their choice, as long as they follow the principle of taking an available spot as soon as it's free.
    ll ans, min = LLONG_MAX;
    for (ll tim : bath)
    {
        min = std::min(tim, min);
    }
    ll l = 0, r = m * min, mid;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (f(bath, mid) >= m + 1)
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return ans;
}
ll min_bath_heap(const vector<ll> &bath, ll m)
{
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    ll n = bath.size();
    for (ll i = 0; i < n; i++)
    {
        pq.push(make_pair(0, bath[i]));
    }

    for (ll i = 0; i < m; i++)
    {
        pair<ll, ll> p = pq.top();
        pq.pop();

        p.first += p.second;
        pq.push(p);
    }

    return pq.top().first;
}
vector<ll> Random_Array(ll n, ll v)
{
    vector<ll> arr(n);
    for (ll i = 0; i < n; ++i)
    {
        arr[i] = static_cast<ll>(static_cast<double>(rand()) / (RAND_MAX + 1.0) * v) + 1;
    }
    return arr;
}
// void test()
// {
//     srand(time(0));

//     ll N = 30;
//     ll V = 10;
//     ll M = 100;
//     ll times = 88888;

//     for (ll i = 0; i < times; ++i)
//     {
//         ll n = rand() % (N + 1);
//         ll m = rand() % (M + 1);
//         if (n == 0 || m == 0)
//             continue;
//         vector<ll> arr = Random_Array(n, V);
//         ll time = min_bath(arr, m), time_heap = min_bath_heap(arr, m);

//         if (time != time_heap)
//         {
//             cout << "Error Found on Test " << (i + 1) << "!" << endl;
//             cout << "Array Size: " << arr.size() << endl;
//             cout << "Array Elements: ";
//             for (ll val : arr)
//             {
//                 cout << val << " ";
//             }
//             cout << endl;
//             cout << "Binary Answer: " << time << endl;
//             cout << "Heap: " << time_heap << endl;
//             return;
//         }
//     }

//     cout << "All " << times << " tests passed successfully!" << endl;
// }

// monster has hp health, each turn, you can choose to either use a sword slash or apply poison.
// sword causes immediate damage in the current turn and poison causes continuous damage starting from the next turn, and it can be stacked, return the minimum number of turns to kill the monster (n turns are available for actions, if the monster is not killed after n turns, it will continue to take poison damage until it dies)?
bool f(const vector<ll> &sword, const vector<ll> &pois, ll hp, ll m)
{
    ll len = sword.size();
    ll n = min(len, m);
    for (ll i = 0, j = 1; i < n; i++, j++)
    {
        hp -= max(pois[i] * (m - j), sword[i]);

        if (hp <= 0)
        {
            return true;
        }
    }

    return false;
}
ll kill_mon(const vector<ll> &sword, const vector<ll> &pois, ll hp)
{
    ll ans = LLONG_MAX;
    ll l = 1, r = hp + 1, m;
    while (l <= r)
    {
        m = (l + r) / 2;
        if (f(sword, pois, hp, m))
        {
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }

    return ans;
}