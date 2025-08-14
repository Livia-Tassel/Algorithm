#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <cstdlib>
#define ll long long
using namespace std;

struct mystack
{
    stack<ll> min, data;
    mystack() {}

    // eg: 3 5 2 7
    // min: 3 3 2 2
    void push(ll value)
    {
        data.push(value);
        if (min.empty() || value <= min.top())
        {
            min.push(value);
        }
        else
        {
            min.push(min.top());
        }
    }

    void pop()
    {
        if (data.empty())
        {
            cout << "empty\n";
            return;
        }
        data.pop();
        min.pop();
    }

    ll get_min()
    {
        if (min.empty())
        {
            cout << "empty\n";
            return -1;
        }
        return min.top();
    }

    ll top()
    {
        if (data.empty())
        {
            cout << "empty\n";
            return -1;
        }
        return data.top();
    }
};

signed main(){
    mystack s;
    s.push(3);
    s.push(5);
    cout << s.get_min() << endl; // 3
    s.push(2);
    s.push(7);
    cout << s.get_min() << endl; // 2
    s.pop();
    cout << s.get_min() << endl; // 2
    s.pop();
    cout << s.get_min() << endl; // 3
    s.pop();
    cout << s.get_min() << endl; // 3
    s.pop();
    cout << s.get_min() << endl; // empty
    return 0;
}