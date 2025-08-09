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

// pop the bottom element of a stack while maintaining the order of the other elements.
ll bottom_pop(stack<ll> &s)
{
    ll ans = s.top();
    s.pop();
    if (s.empty())
    {
        return ans;
    }
    else
    {
        ll last = bottom_pop(s);
        s.push(ans);
        return last;
    }
}

void reverse(stack<ll> &s)
{
    if (s.empty())
    {
        return;
    }

    ll num = bottom_pop(s);
    reverse(s);
    s.push(num);
}
