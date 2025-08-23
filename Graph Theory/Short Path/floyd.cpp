#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <unordered_set>
#include <deque>
#define ll long long
using namespace std;
const ll inf = 99999;
ll n;
ll dist[101][101];
void floyd()
{
    for (ll k = 0; k < n; ++k)
    {
        for (ll i = 0; i < n; ++i)
        {
            for (ll j = 0; j < n; ++j)
            {
                if (dist[i][k] != inf && dist[k][j] != inf)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}