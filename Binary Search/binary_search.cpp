#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define ll long long
using namespace std;

ll search_exit(const ll arr[], ll size, ll num)
{
    if (arr == nullptr || size == 0)
    {
        return -1;
    }

    ll l = 0;
    ll r = size - 1;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        if (arr[mid] == num)
        {
            return mid;
        }
        else if (arr[mid] < num)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return -1;
}

ll search_exit_correct(const ll arr[], ll size, ll num)
{
    for (ll i = 0; i < size; ++i)
    {
        if (arr[i] == num)
        {
            return i;
        }
    }
    return -1;
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

void check_search_exit()
{
    srand(time(0));

    ll N = 10;
    ll V = 100;
    ll times = 100000;

    for (ll i = 0; i < times; ++i)
    {
        ll n = rand() % (N + 1);
        vector<ll> arr = Random_Array(n, V);
        sort(arr.begin(), arr.end());

        ll num_to_search = static_cast<ll>(static_cast<double>(rand()) / (RAND_MAX + 1.0) * V) + 1;

        ll result_exit = search_exit(arr.data(), arr.size(), num_to_search);
        ll result_correct = search_exit_correct(arr.data(), arr.size(), num_to_search);

        if (result_exit != result_correct)
        {
            cout << "Error Found on Test " << (i + 1) << "!" << endl;
            cout << "Array Size: " << arr.size() << endl;
            cout << "Array Elements: ";
            for (ll val : arr)
            {
                cout << val << " ";
            }
            cout << endl;
            cout << "Number to Search: " << num_to_search << endl;
            cout << "Binary Search Result: " << result_exit << endl;
            cout << "Linear Search Result: " << result_correct << endl;
            return;
        }
    }
    cout << "All " << times << " tests passed successfully!" << endl;
}

// search the leftmost position of an element greater than or equal to num
ll search_greater_equal(const ll arr[], ll size, ll num)
{
    if (arr == nullptr || size == 0)
    {
        return -1;
    }

    ll l = 0;
    ll r = size - 1;
    ll ans = -1;
    while (l <= r)
    {
        ll mid = (l + r) / 2;
        // ll min = l + (r - l) / 2; // prevent overflow
        if (arr[mid] >= num)
        {
            ans = mid; // record the position
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return ans;
}

// search the rightmost position of an element less than or equal to num
ll search_less_equal(const ll arr[], ll size, ll num)
{
    if (arr == nullptr || size == 0)
    {
        return -1;
    }

    ll l = 0;
    ll r = size - 1;
    ll ans = -1;
    while (l <= r)
    {
        ll mid = (l + r) / 2;
        if (arr[mid] <= num)
        {
            ans = mid; // record the position
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return ans;
}

// any two non-adjacent numbers are not equal, return a peak element ('small - large - small').
ll search_peak(const ll arr[], ll size)
{
    if (size == 1)
    {
        // assume arr[-1] and arr[size] are very small.
        return 0;
    }

    // size >= 2, verify if arr[0] and arr[n-1] are peak elements.
    if (arr[0] > arr[1])
    {
        return 0;
    }
    if (arr[size - 1] > arr[size - 2])
    {
        return size - 1;
    }

    // based on the function's trend, [1, size-2] must contain at least one peak.
    ll l = 1, r = size - 2, ans = -1;
    while (l <= r)
    {
        ll mid = (l + r) / 2;
        if (arr[mid] < arr[mid - 1])
        {
            r = mid - 1;
        }
        else if (arr[mid] < arr[mid + 1])
        {
            l = mid + 1;
        }
        else
        {
            ans = mid; // arr[mid] is a peak element.
            break;
        }
    }
    return ans;
}
signed main()
{
    check_search_exit();

    return 0;
}