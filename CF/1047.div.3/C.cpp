#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <numeric>
#include <unordered_map>
#define ll long long
using namespace std;
using vl = vector<ll>;

ll solve(ll a, ll b)
{
    ll pro = a * b;
    if (pro % 2 == 1)
    {
        cout << pro + 1 << endl;
    }
    else
    {
        if (b % 2 == 0 && (pro / 2) % 2 == 0)
        {
            cout << pro / 2 + 2 << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
}
signed main()
{
    ll t, a, b;
    cin >> t;
    while (t--)
    {
        cin >> a >> b;
        solve(a, b);
    }
}