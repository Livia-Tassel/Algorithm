#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <map>
#define ll long long
using namespace std;
const ll MAXN = 5001, MAXM = 200001;

// undirected weighted graph
ll root[MAXN];
ll n, m;

void init()
{
    for (ll i = 1; i < n + 1; i++)
    {
        root[i] = i;
    }
}

ll find(ll x)
{
    return root[x] != x ? root[x] = find(root[x]) : x;
}

bool un(ll x, ll y)
{
    ll fx = find(x), fy = find(y);
    if (fx != fy)
    {
        root[fy] = fx;
        return true;
    }
    else
    {
        return false;
    }
}
