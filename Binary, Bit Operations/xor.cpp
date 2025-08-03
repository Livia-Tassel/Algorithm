#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define ll long long
using namespace std;

// Summary of XOR:
// 1. xor is essentially addition without carry.
// 2. xor satisfies commutative and associative laws, etc. (easily derived from property 1).
// 3. 0 ^ x = x (0 xor x equals x), x ^ x = 0 (x xor x equals 0).
// 4. from a ^ b = c, can be deduced that b ^ c = a and a ^ c = b (derived from properties 2 and 3).

void swap_xor(ll &a, ll &b)
{
    a = a ^ b; // a = a' ^ b', b = b'
    b = a ^ b; // b = (a' ^ b') ^ b' = a', a = a' ^ b'
    a = a ^ b; // a = (a' ^ b') ^ a' = b', b = a'
}

ll sign(ll num)
{
    return (num >> 63) ^ 1; // extract the sign bit (0 for negative, 1 for positive)
}

ll flip(ll n)
{
    return n ^ 1;
}

ll max_xor(ll &a, ll &b)
{
    ll c = a - b;
    ll returna = sign(c);
    // c < 0 → a < b, returna = 0; c > 0 → a > b, returna = 1
    ll returnb = flip(returna); // flip the sign, so 1 means a > b, 0 means a < b
    return a * returna + b * returnb;
}

ll max_xor_overflow(ll &a, ll &b)
{
    ll c = a - b;
    ll sa = sign(a);
    ll sb = sign(b);
    ll sc = sign(c);

    // diffab = 1, a and b have different signs; diffab = 0, a and b have the same sign
    ll diffab = sa ^ sb;
    ll sameab = flip(diffab);

    // diffab = 1 && sa = 1; diffab = 0, sc = 1
    ll returna = sa * diffab + sc * sameab;
    // diffab = 1 && sb = 1; diffab = 0, sc = 0
    ll returnb = flip(returna);

    return a * returna + b * returnb;
}

ll missing_num(vector<ll> &nums)
{
    ll n = nums.size();
    ll total_xor = 0;
    for (ll i = 0; i < n + 1; ++i)
    {
        total_xor ^= i; // xor from 0 to n
    }

    for (ll num : nums)
    {
        total_xor ^= num; // xor remain elements
    }

    return total_xor; // the missing number
}

ll odd_and_even(vector<ll> &nums)
{
    // only 'x' appears an odd number of times; all other numbers appear an even number of times, return x
    ll x = 0;
    for (ll num : nums)
    {
        x ^= num; // xor all numbers
    }
    return x;
}

ll brain_kernighan(ll x)
{
    return x & ((~x) + 1); // x & -x, isolate the rightmost 1 bit
}

void odd_and_even_plus(vector<ll> &nums)
{
    // only 'a' and 'b' appears an odd number of times; all other numbers appear an even number of times
    ll total_xor = 0, single_xor = 0;
    for (ll num : nums)
    {
        total_xor ^= num; // total_xor = a ^ b
    }

    ll rightmost_bit = brain_kernighan(total_xor);

    for (ll num : nums)
    {
        if (num & rightmost_bit) // group the numbers based on the rightmost bit
        {
            single_xor ^= num; // single_xor = a or b
        }
    }

    cout << single_xor << " " << (total_xor ^ single_xor); // b = total_xor ^ a
}

ll cnt_m(vector<ll> &nums, ll m)
{
    ll cnt[64] = {0}; // count of 1s of each bit position

    // only 'ans' appears less than 'm' times; all other numbers appear exactly 'm' times.
    ll ans = 0;
    for (ll num : nums)
    {
        for (ll i = 0; i < 64; ++i)
        {
            cnt[i] += (num >> i) & 1; // count the number of 1s on the i-th bit position
        }
    }

    for (ll i = 0; i < 64; ++i)
    {
        if (cnt[i] % m != 0)
        {
            ans |= (1LL << i);
        }
    }

    return ans;
}

signed main()
{
    ll a = 5, b = 10;
    cout << "before swap: a = " << a << ", b = " << b << endl;
    swap_xor(a, b);
    cout << "after swap: a = " << a << ", b = " << b << endl;

    max_xor(a, b);
    cout << "max_xor: " << max_xor(a, b) << endl
         << "max_xor_overflow: " << max_xor_overflow(a, b) << endl;

    vector<ll> nums = {0, 1, 2, 4, 5}; // missing 3
    cout << "missing_num: " << missing_num(nums) << endl;

    vector<ll> odd_even_nums = {1, 2, 3, 2, 1, 3, 4};
    cout << "odd_and_even: " << odd_and_even(odd_even_nums) << endl;

    vector<ll> odd_even_plus_nums = {1, 2, 3, 2, 1, 3, 4, 5};
    cout << "odd_and_even_plus: ";
    odd_and_even_plus(odd_even_plus_nums);

    vector<ll> cnt_m_nums = {1, 2, 3, 1, 2, 3, 8, 1, 2, 3};
    ll m = 3;
    cout << "\ncnt_m: " << cnt_m(cnt_m_nums, m) << endl;
}