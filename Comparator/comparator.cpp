#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#define ll long long
using namespace std;

vector<ll> Random_Array(ll n, ll v)
{
    vector<ll> arr(n);
    for (ll i = 0; i < n; ++i)
    {
        // rand() generates an integer between 0 and rand_max.
        // use static_cast<double>(rand()) / rand_max to get a double in [0.0, 1.0)
        // static_cast<ll>(randomdouble * v) -> ll in [0, v) range, still uniformly distributed
        // static_cast<ll>(randomdouble * v) + 1 -> ll in [1, v] range, still uniformly distributed
        double randomdouble = static_cast<double>(rand()) / (RAND_MAX + 1.0);

        arr[i] = static_cast<ll>(randomdouble * v) + 1;
    }
    return arr;
}

vector<ll> Copy_Array(const vector<ll> &arr)
{
    vector<ll> copy(arr);
    return copy;
}

bool Same_Array(const vector<ll> &arr1, const vector<ll> &arr2)
{
    if (arr1.size() != arr2.size())
        return false;
    for (size_t i = 0; i < arr1.size(); ++i)
    {
        if (arr1[i] != arr2[i])
            return false;
    }
    return true;
}

void Selection_Sort(vector<ll> &arr)
{
    ll n = arr.size();
    for (ll i = 0; i < n - 1; ++i)
    {
        ll min_index = i;
        for (ll j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        swap(arr[i], arr[min_index]);
    }
}
void Insertion_Sort(vector<ll> &arr)
{
    ll n = arr.size();
    for (ll i = 1; i < n; ++i)
    {
        ll key = arr[i];
        ll j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

signed main()
{
    ll N = 10;  // max size of the array
    ll V = 100; // range of values
    ll times = 1000;
    while (times--)
    {
        ll n = rand() % N; // random size of the array between 0 and N-1
        vector<ll> arr = Random_Array(n, V);

        // cout << "Random Array: ";
        // for (ll i = 0; i < n; ++i)
        // {
        //     cout << arr[i] << " ";
        // }
        // cout << endl;

        vector<ll> ass = Copy_Array(arr);
        vector<ll> ais = Copy_Array(arr);
        Selection_Sort(ass);
        Insertion_Sort(ais);
        if (!Same_Array(ass, ais))
        {
            cout << "Error!" << endl;
            cout << "Original Array: ";
            for (ll i = 0; i < n; ++i)
            {
                cout << arr[i] << " ";
            }
            cout << endl;

            cout << "Selection Sort Result: ";
            for (ll i = 0; i < n; ++i)
            {
                cout << ass[i] << " ";
            }
            cout << endl;

            cout << "Insertion Sort Result: ";
            for (ll i = 0; i < n; ++i)
            {
                cout << ais[i] << " ";
            }
            cout << endl;
        }
        else
        {
            cout << "Success!" << endl;
        }
    }

    return 0;
}