#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#define ll long long
using namespace std;

// n stones, the first player takes any amount, subsequent players take 1 to 2x stones (x is the previous amount), find the minimum first move to win.
// if n equals fibo (1 1 2 3 5 8...), take all the stones;
// else n = f_1 + f_2 + ... (f_1, f_2, ... are fiboes), take f_1 stones;
const ll maxn = 1000000000000001L, maxm = 101;
ll f[maxm];
ll size;
void build()
{
    f[0] = 1;
    f[1] = 2;
    size = 1;
    while (f[size] < maxn)
    {
        f[size + 1] = f[size] + f[size - 1];
        size++;
    }
}
ll bs(ll n)
{
    ll l = 0, r = size;
    ll ans = -1;
    while (r >= l)
    {
        ll m = l + (r - l) / 2;
        if (f[m] > n)
        {
            r = m - 1;
        }
        else
        {
            ans = f[m];
            l = m + 1;
        }
    }
    return ans;
}
ll fibo(ll n)
{
    ll ans = -1, find;
    while (n != 1 && n != 2)
    {
        find = bs(n);
        if (n == find)
        {
            ans = find;
            break;
        }
        else
        {
            n -= find;
        }
    }
    return ans != -1 ? ans : n;
}