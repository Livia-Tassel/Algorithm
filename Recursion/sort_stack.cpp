#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#define ll long long
using namespace std;
const ll MAXN = 10001;

ll depth(stack<ll> &s)
{
    if (s.empty())
    {
        return 0;
    }

    ll num = s.top();
    s.pop();
    ll d = depth(s) + 1;
    s.push(num);

    return d;
}

ll stack_max(stack<ll> &s, ll depth)
{
    if (depth == 0)
    {
        return LLONG_MIN;
    }

    ll num = s.top();
    s.pop();
    ll m = max(num, stack_max(s, depth - 1));
    s.push(num);

    return m;
}

ll times(stack<ll> &s, ll depth, ll max)
{
    if (depth == 0)
    {
        return 0;
    }

    ll t;
    ll num = s.top();
    s.pop();
    ll ut = times(s, depth - 1, max);
    num == max
        ? t = ut + 1
        : t = ut;
    s.push(num);

    return t;
}

void down(stack<ll> &s, ll depth, ll max, ll times)
{
    if (depth == 0)
    {
        for (ll i = 0; i < times; i++)
        {
            s.push(max);
        }
    }
    else
    {
        ll num = s.top();
        s.pop();
        down(s, depth - 1, max, times);
        if (num != max)
        {
            s.push(num);
        }
    }
}

void sort(stack<ll> &s)
{
    ll d = depth(s);
    while (d > 0)
    {

        ll m = stack_max(s, d);
        ll k = times(s, d, m);
        down(s, d, m, k);
        cout << "d=" << d << ",m=" << m << ",k=" << k << endl;
        d -= k;
    }
}

void print_stack(stack<ll> s)
{
    cout << "Top -> [ ";
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << "]" << endl;
}

signed main()
{
    stack<ll> my_stack;
    my_stack.push(3);
    my_stack.push(1);
    my_stack.push(5);
    my_stack.push(2);
    my_stack.push(5);

    cout << "original stack:" << endl;
    print_stack(my_stack); // Top -> [ 5 2 5 1 3 ]

    sort(my_stack);

    cout << "\nsorted stack:" << endl;
    print_stack(my_stack); // Top -> [ 1 2 3 5 5 ]

    return 0;
}