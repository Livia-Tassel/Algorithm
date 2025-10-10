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

void solve()
{
    ll n;
    cin >> n;
    ll co = 0, ct = 0;
    string s;
    cin >> s;
    for (ll i = 0; i < s.length(); i++)
    {
        s[i] == '1' ? ct++ : co++;
    }
    cout << (n - 1) * ct + co << endl;
}
signed main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}