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
const ll maxn = 2e5 + 5;
const int high = 31;

struct node
{
    int chl[2];
    int last; // maximum id in this subtree
    node()
    {
        chl[0] = chl[1] = -1;
        last = -1;
    }
};
using vn = vector<node>;
ll gs(vn &a)
{
    return a.size();
}

// find the max j, where val ^ a[j] >= bd
int find(vn &trie, int val, int bd)
{
    int res = -1;
    int cur = 0; // root
    bool ok = true;
    for (int pos = high; ok && pos >= 0; --pos)
    {
        int x_bit = (val >> pos) & 1;
        int k_bit = (bd >> pos) & 1;
        auto &chl = trie[cur].chl;
        if (k_bit == 1)
        {
            // must have chl[x_bit ^ 1] branch
            if (chl[x_bit ^ 1] != -1)
            {
                cur = chl[x_bit ^ 1];
            }
            else
            {
                ok = false;
            }
        }
        else
        {
            if (chl[x_bit ^ 1] != -1)
            {
                res = max(res, trie[chl[x_bit ^ 1]].last);
            }
            if (chl[x_bit] != -1)
            {
                cur = chl[x_bit];
            }
            else
            {
                ok = false;
            }
        }
    }
    if (ok)
    {
        res = max(res, trie[cur].last);
    }
    return res;
}

void add(vn &trie, int val, int id)
{
    int cur = 0;
    trie[cur].last = max(trie[cur].last, id);
    for (int pos = high; pos >= 0; --pos)
    {
        int x_bit = (val >> pos) & 1;
        if (trie[cur].chl[x_bit] == -1)
        {
            trie[cur].chl[x_bit] = gs(trie);
            trie.emplace_back();
        }
        cur = trie[cur].chl[x_bit];
        trie[cur].last = max(trie[cur].last, id);
    }
}

void solve()
{
    int n;
    ll k_ll;
    cin >> n >> k_ll;
    int k = (int)k_ll;
    vl a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    if (k == 0)
    {
        cout << 1 << '\n';
        return;
    }

    int ans = n + 1;
    vn trie(1);

    for (int i = 0; i < n; ++i)
    {
        // search before add
        int y = find(trie, a[i], k);
        if (y != -1)
        {
            ans = min(ans, i - y + 1);
        }
        add(trie, a[i], i);
    }

    if (ans == n + 1)
        cout << -1 << '\n';
    else
        cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t))
        return 0;
    while (t--)
        solve();
    return 0;
}
