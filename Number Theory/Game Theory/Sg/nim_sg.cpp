#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#define ll long long
using namespace std;
ll arr[10001];
string nim(ll n)
{
    if (n == 0)
    {
        return "sec";
    }

    ll max = 0;
    for (ll i = 0; i < n; i++)
    {
        max = std::max(max, arr[i]);
    }

    ll sg[max + 1];
    memset(sg, 0, sizeof(sg));
    bool appear[max + 1];

    for (ll i = 1; i < max + 1; i++)
    {
        memset(appear, false, sizeof(appear));
        for (ll j = 0; j < i; j++)
        {
            appear[j] = true;
        }

        for (ll s = 0; s < max + 1; s++)
        {
            if (!appear[s])
            {
                sg[i] = s;
                break;
            }
        }
    }

    ll eor = 0;
    for (ll i = 0; i < n; i++)
    {
        eor ^= sg[arr[i]];
    }

    return eor != 0 ? "fir" : "sec";
}
