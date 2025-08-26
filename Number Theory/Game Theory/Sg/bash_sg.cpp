#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#define ll long long
using namespace std;

string bash(ll n, ll m)
{
    ll sg[n + 1];
    memset(sg, 0, sizeof(sg));
    bool appear[m + 1];

    for (ll i = 1; i < n + 1; i++)
    {
        memset(appear, false, sizeof(appear));
        for (ll j = 1; j < m + 1 && i - j >= 0; j++)
        {
            appear[sg[i - j]] = true;
        }

        ll mex = 0;
        while (m >= mex && appear[mex])
        {
            mex++;
        }
        sg[i] = mex;
    }

    return sg[n] != 0 ? "fir" : "sec";
}

// bash game, but have two piles of stones, a b
string bash(ll a, ll b, ll m)
{
    // 0 1 2 3 4 5 6 7 8 9  m = 3
    // 0 1 2 3 0 1 2 3 0 1
    // sg[i] = i % (m + 1)
    return a % (m + 1) != b % (m + 1) ? "fir" : "sec";
}
