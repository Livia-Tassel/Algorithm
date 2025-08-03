#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#define ll long long
using namespace std;
const ll MAXN = 10001;
ll arr[MAXN];

// complete binary tree implemented using an array, the parent node of each node i is at index (i-1)/2, its left child is at 2*i+1, and its right child is at 2*i+2.
//   (i-1)/2
//       \
//       i
//      / \
// 2*i+1   2*i+2

void heapify(ll i, ll size)
{
    ll l = 2 * i + 1;
    // l < size means the left child exists
    while (l < size)
    {
        ll max_son, dex;
        l + 1 < size ? max_son = max(arr[l], arr[l + 1]) : max_son = arr[l];
        max_son == arr[l] ? dex = l : dex = l + 1;
        if (arr[i] < max_son)
        {
            swap(arr[i], arr[dex]);
            i = dex;
        }
        else
        {
            break;
        }
        l = 2 * i + 1;
    }
}

// arr[i] = x
void heap_insert(ll i)
{
    // when reach the top of the heap, 0 = (0-1)/2, stop
    while (arr[i] > arr[(i - 1) / 2])
    {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void build_heap_up_down(ll n)
{
    for (ll i = 0; i < n; i++)
    {
        heap_insert(i);
    }
}

void build_heap_down_up(ll n)
{
    for (ll i = n - 1; i >= 0; i--)
    {
        heapify(i, n);
    }
}

void heap_sort(ll n)
{
    build_heap_down_up(n);
    // build_heap_up_down(n);
    ll size = n;
    while (size > 1)
    {
        swap(arr[0], arr[size - 1]);
        size--;
        heapify(0, size);
    }
}

signed main()
{
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    heap_sort(n);
    for (ll i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}