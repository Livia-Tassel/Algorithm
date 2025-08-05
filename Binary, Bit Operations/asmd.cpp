#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define ll long long
using namespace std;

// support addition using bitwise operations.
ll add_using_bitwise(ll a, ll b)
{
    while (b != 0)
    {
        ll carry = a & b;
        a = a ^ b; // sum without carry
        b = carry << 1;
    }
    return a;
}

// support subtraction using bitwise operations.
ll subtract_using_bitwise(ll a, ll b)
{
    ll neg_b = add_using_bitwise(~b, 1); // negation of b
    return add_using_bitwise(a, neg_b);
}

// support multiplication using bitwise operations.
ll multiply_using_bitwise(ll a, ll b)
{
    ll result = 0;
    bool negative = (a < 0) ^ (b < 0);

    if (a < 0)
        a = add_using_bitwise(~a, 1);
    if (b < 0)
        b = add_using_bitwise(~b, 1);

    while (b > 0)
    {
        if (b & 1)
            result = add_using_bitwise(result, a);
        a <<= 1;
        b >>= 1;
    }

    return negative ? add_using_bitwise(~result, 1) : result;
}

// support division using bitwise operations.
ll divide_using_bitwise(ll a, ll b)
{
    bool negative = (a < 0) ^ (b < 0);

    ll abs_a = (a < 0) ? add_using_bitwise(~a, 1) : a;
    ll abs_b = (b < 0) ? add_using_bitwise(~b, 1) : b;

    ll ans = 0;
    for (int i = 63; i >= 0; i = subtract_using_bitwise(i, 1))
    {
        if ((abs_a >> i) >= abs_b)
        {
            abs_a = subtract_using_bitwise(abs_a, abs_b << i);
            ans |= (1LL << i);
        }
    }

    return negative ? add_using_bitwise(~ans, 1) : ans;
}

signed main()
{
    ll a = 2, b = -7;
    cout << "addition: " << add_using_bitwise(a, b) << endl;
    cout << "subtraction: " << subtract_using_bitwise(a, b) << endl;
    cout << "multiplication: " << multiply_using_bitwise(a, b) << endl;
    cout << "division: " << divide_using_bitwise(a, b) << endl;
    return 0;
}