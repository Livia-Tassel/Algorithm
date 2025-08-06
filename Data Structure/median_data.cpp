#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <queue>
#include <set>
#include <iomanip>
#include <cmath>
#define ll long long
using namespace std;

// quickly find the median of a data stream.
struct median_data
{
    // the smaller half is in the max-heap, and the larger half is in the min-heap.
    priority_queue<ll> max_heap;
    priority_queue<ll, vector<ll>, greater<ll>> min_heap;

    void add(ll v)
    {
        if (max_heap.empty() || max_heap.top() >= v)
        {
            max_heap.push(v);
        }
        else
        {
            min_heap.push(v);
        }
        balance();
    }

    ll get_median()
    {
        if (max_heap.size() == min_heap.size())
        {
            return (max_heap.top() + min_heap.top()) / 2;
        }
        else if (max_heap.size() > min_heap.size())
        {
            return max_heap.top();
        }
        else
        {
            return min_heap.top();
        }
    }

    void balance()
    {
        if (max_heap.size() > min_heap.size())
        {
            if (max_heap.size() - min_heap.size() == 2)
            {
                min_heap.push(max_heap.top());
                max_heap.pop();
            }
        }
        else
        {
            if (min_heap.size() - max_heap.size() == 2)
            {
                max_heap.push(min_heap.top());
                min_heap.pop();
            }
        }
    }
};

signed main()
{
    median_data md;

    cout << "\n--- test 1: processing a stream of numbers ---" << endl;
    cout << fixed << setprecision(1);

    ll data_stream[] = {5, 1, 10, 3, 7};
    vector<ll> current_data;

    for (ll v : data_stream)
    {
        current_data.push_back(v);
        sort(current_data.begin(), current_data.end());

        cout << "added " << v << ", current stream: [";
        for (size_t i = 0; i < current_data.size(); ++i)
        {
            cout << current_data[i] << (i == current_data.size() - 1 ? "" : ", ");
        }
        cout << "]" << endl;

        md.add(v);
        cout << "  -> median: " << md.get_median() << endl;
    }

    return 0;
}