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
ll where;

void push(stack<ll> &nums, stack<char> &ops, ll cur, char op)
{
    ll n = nums.size();
    if (n == 0 || ops.top() == '+' || ops.top() == '-')
    {
        nums.push(cur);
        ops.push(op);
    }
    else
    {
        ll num = nums.top();
        nums.pop();
        char top = ops.top();
        ops.pop();

        if (top == '*')
        {
            nums.push(num * cur);
        }
        else
        {
            nums.push(num / cur);
        }
        ops.push(op);
    }
}

ll calculate(stack<ll> &nums, stack<char> &ops)
{
    vector<ll> num_vec;
    vector<char> op_vec;
    ops.pop();

    while (!nums.empty())
    {
        num_vec.push_back(nums.top());
        nums.pop();
    }
    while (!ops.empty())
    {
        op_vec.push_back(ops.top());
        ops.pop();
    }
    reverse(num_vec.begin(), num_vec.end());
    reverse(op_vec.begin(), op_vec.end());

    if (num_vec.empty())
    {
        return 0;
    }

    ll ans = num_vec[0];
    for (size_t i = 0; i < op_vec.size(); ++i)
    {
        if (op_vec[i] == '+')
        {
            ans += num_vec[i + 1];
        }
        else if (op_vec[i] == '-')
        {
            ans -= num_vec[i + 1];
        }
    }
    return ans;
}

ll f(ll i, const string &s)
{
    stack<ll> nums;
    stack<char> ops;
    ll cur = 0;

    while (i < s.length() && s[i] != ')')
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            cur = cur * 10 + s[i++] - '0';
        }
        else if (s[i] != '(')
        {
            push(nums, ops, cur, s[i++]);
            cur = 0;
        }
        else
        {
            cur = f(i + 1, s);
            i = where + 1;
        }
    }
    push(nums, ops, cur, '+');
    where = i;
    return calculate(nums, ops);
}

ll evaluation(const string &exp)
{
    return f(0, exp);
}

signed main()
{
    string expression = "10-(2*3-1)+4*2"; // 10 - (5) + 8 = 13
    cout << "evaluating '" << expression << "'" << endl;
    ll result = evaluation(expression);
    cout << "result: " << result << endl;

    return 0;
}