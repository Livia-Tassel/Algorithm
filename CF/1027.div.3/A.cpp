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
    string s;
    cin >> s;
    ll tar = stoll(s);
    ll sq = (ll)sqrt(tar);
    if (sq * sq == tar)
    {
        cout << 0 << " " << sq << endl;
        return;
    }
    cout << -1 << endl;
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