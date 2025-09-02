#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;
using ll = long long;
using vb = vector<bool>;
using vl = vector<ll>;

// n log n
ll LIS(vl &arr)
{
    if (arr.empty())
        return 0;

    vl tails;
    for (ll num : arr)
    {
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if (it == tails.end())
        {
            tails.push_back(num);
        }
        else
        {
            *it = num;
        }
    }
    return tails.size();
}

ll LDS(vl &arr)
{
    reverse(arr.begin(), arr.end());
    return LIS(arr);
}