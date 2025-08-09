#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#define ll long long
using namespace std;
const ll MAXN = 10001;
vector<ll> path(MAXN);

void f(const vector<ll> &arr, ll i, ll size, list<list<ll>> &ans)
{
    if (i == arr.size())
    {
        list<ll> l;
        for (ll j = 0; j < size; j++)
        {
            l.push_back(path[j]);
        }
        ans.push_back(l);
    }
    else
    {
        ll j = i + 1;
        while (j < arr.size() && arr[i] == arr[j])
        {
            j++;
        }

        f(arr, j, size, ans);
        for (ll k = i; k < j; k++)
        {
            path[size++] = arr[k];
            f(arr, j, size, ans);
        }
    }
}

list<list<ll>> subsets(vector<ll> arr)
{
    list<list<ll>> ans;
    sort(arr.begin(), arr.end());
    f(arr, 0, 0, ans);
    return ans;
}

signed main()
{
    vector<ll> arr(6);
    arr[0] = 1, arr[1] = 2, arr[2] = 1, arr[3] = 2, arr[4] = 2, arr[5] = 3;
    list<list<ll>> ans = subsets(arr);
    for (const auto &list : ans)
    {
        for (ll val : list)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}

