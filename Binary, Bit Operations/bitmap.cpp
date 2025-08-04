#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <set>
#define ll long long
using namespace std;
const ll MAX_SIZE = 1000000;

struct bitmap
{
    vector<ll> set;

    void
    bitmap_set(ll n)
    {
        // set bitmap, supports "crud" operations for all numbers from 0 to n-1
        set.resize((n + 63) / 64, 0); // each element can store 64 bits
    }

    void insert(ll num)
    {
        set[num / 64] |= (1LL << (num % 64));
    }

    void erase(ll num)
    {
        set[num / 64] &= ~(1LL << (num % 64));
    }

    void reverse(ll num)
    {
        set[num / 64] ^= (1LL << (num % 64));
    }

    bool contains(ll num)
    {
        return (set[num / 64] & (1LL << (num % 64))) != 0;
    }
};

void test_bitmap()
{
    ll n = 1000, times = 10000;
    cout << "test start!" << endl;

    bitmap bm;
    bm.bitmap_set(n);
    set<ll> s;

    while (times--)
    {
        double randomdouble = static_cast<double>(rand()) / (RAND_MAX + 1.0);
        ll num = static_cast<ll>(randomdouble * n);

        if (randomdouble < 0.33)
        {
            bm.insert(num);
            s.insert(num);
        }
        else if (randomdouble < 0.66)
        {
            bm.erase(num);
            s.erase(num);
        }
        else
        {
            bm.reverse(num);
            if (s.count(num))
            {
                s.erase(num);
            }
            else
            {
                s.insert(num);
            }
        }
    }
    cout << "test end!" << endl;

    for (ll i = 0; i < n; i++)
    {
        if (bm.contains(i) != s.count(i))
        {
            cerr << "error: " << i << endl;
        }
    }
    cout << "test passed!" << endl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    test_bitmap();

    return 0;
}