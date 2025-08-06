#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <queue>
#include <set>
#include <cmath>
#include <list>
#define ll long long
using namespace std;

struct freq_stack
{
    ll top_times;
    map<ll, list<ll>> cnt;
    map<ll, ll> value_times;
    freq_stack() : top_times(0) {}

    void push(ll v)
    {
        ll cur_times = ++value_times[v];
        cnt[cur_times].push_back(v);
        top_times = max(value_times[v], top_times);
    }

    ll pop()
    {
        ll remove = cnt[top_times].back();
        cnt[top_times].pop_back();
        if (cnt[top_times].empty())
        {
            cnt.erase(top_times--);
        }

        if (value_times[remove] == 1)
        {
            value_times.erase(remove);
        }
        else
        {
            value_times[remove]--;
        }
        return remove;
    }
};

signed main()
{
    freq_stack fs;
    cout << "push(5), push(7), push(5), push(7), push(4), push(5)" << endl;
    fs.push(5);
    fs.push(7);
    fs.push(5);
    fs.push(7);
    fs.push(4);
    fs.push(5);

    // 5(3), 7(2), 4(1)。 top_times = 3.
    cout << "pop: " << fs.pop() << endl; // 5
    cout << "pop: " << fs.pop() << endl; // 7
    cout << "pop: " << fs.pop() << endl; // 5
    cout << "pop: " << fs.pop() << endl; // 4
    cout << "pop: " << fs.pop() << endl; // 7
    cout << "pop: " << fs.pop() << endl; // 5

    return 0;
}