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

void f(vector<ll> &arr, ll i, list<list<ll>> &ans)
{
    if (i == arr.size())
    {
        list<ll> l;
        for (ll val : arr)
        {
            l.push_back(val);
        }
        ans.push_back(l);
    }
    else
    {
        for (ll j = i; j < arr.size(); j++)
        {
            swap(arr[i], arr[j]);
            f(arr, i + 1, ans);
            swap(arr[i], arr[j]);
        }
    }
}

// repeat number
void fr(vector<ll> &arr, ll i, list<list<ll>> &ans)
{
    if (i == arr.size())
    {
        list<ll> l;
        for (ll val : arr)
        {
            l.push_back(val);
        }
        ans.push_back(l);
    }
    else
    {
        set<ll> s;
        for (ll j = i; j < arr.size(); j++)
        {
            // attempt will only be made when arr[j] first arrives at position i.
            if (!s.count(arr[j]))
            {
                s.insert(arr[j]);
                swap(arr[i], arr[j]);
                fr(arr, i + 1, ans);
                swap(arr[i], arr[j]);
            }
        }
    }
}

list<list<ll>> permulations(vector<ll> arr)
{
    list<list<ll>> ans;
    // f(arr, 0, ans);
    fr(arr, 0, ans);
    return ans;
}

signed main()
{
    vector<ll> arr(6);
    arr[0] = 1, arr[1] = 2, arr[2] = 3, arr[3] = 4, arr[4] = 5, arr[5] = 6;
    list<list<ll>> ans = permulations(arr);
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