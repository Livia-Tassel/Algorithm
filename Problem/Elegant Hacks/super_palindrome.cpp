#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#define ll long long
using namespace std;

ll even_enlarge(ll seed)
{
    ll num = seed;
    while (seed)
    {
        num = num * 10 + seed % 10;
        seed /= 10;
    }
    return num;
}

ll odd_enlarge(ll seed)
{
    ll num = seed;
    seed /= 10;
    while (seed)
    {
        num = num * 10 + seed % 10;
        seed /= 10;
    }
    return num;
}

bool palindrome(ll x)
{
    ll offset = 1;
    while (x / offset >= 10)
    {
        offset *= 10;
    }

    // x        52725
    // offset   10000
    while (x != 0)
    {
        if (x / offset != x % 10)
        {
            return false;
        }
        x = (x % offset) / 10;
        offset /= 100;
    }

    return true;
}

bool check(ll x, ll l, ll r)
{
    return x >= l && x <= r && palindrome(x);
}

// Calculate the count of super palindromic numbers between l and r. The super palindromic number is one that is a palindrome and its square root is also a palindrome.
ll super_palindrome(ll l, ll r)
{
    ll limit = (ll)sqrt((double)r);
    ll seed = 1, num = 0, ans = 0;

    do
    {
        // even palindrome
        // 123 → 123321
        num = even_enlarge(seed);
        if (check(num * num, l, r))
        {
            cout << "x: " << num * num << endl;
            ans++;
        }

        // odd palindrome
        // 123 → 12321
        num = odd_enlarge(seed);
        if (check(num * num, l, r))
        {
            ans++;
            cout << "x: " << num * num << endl;
        }

        seed++;
    } while (num < limit);

    return ans;
}

signed main()
{
    ll ans = super_palindrome(0, LLONG_MAX);
    cout << ans << endl;
    return 0;
}