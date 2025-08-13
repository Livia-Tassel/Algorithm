#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <bit>
#include <set>
#define ll long long
using namespace std;
const ll MAXN = 100001;
const ll S = 2; // 0, 1
ll trie[MAXN][S];
ll cnt, high;

void insert(ll num)
{
    ll cur = 1; // root
    for (ll i = high, path; i >= 0; i--)
    {
        path = (num >> i) & 1;
        if (trie[cur][path] == 0)
        {
            trie[cur][path] = ++cnt;
        }
        cur = trie[cur][path];
    }
}

void build(const vector<ll> &arr)
{
    cnt = 1;
    ll max = LLONG_MIN;
    for (ll num : arr)
    {
        max = std::max(num, max);
    }
    high = 63 - __builtin_clzll(max); // max != 0

    for (ll num : arr)
    {
        insert(num);
    }
}

void clear()
{
    for (ll i = 0; i <= cnt; i++)
    {
        memset(trie[i], 0, sizeof(trie[i]));
    }
}

ll f(ll num)
{
    ll ans = 0, cur = 1;
    for (ll i = high, path; i >= 0; i--)
    {
        path = !((num >> i) & 1);
        if (trie[cur][path] == 0)
        {
            ans |= (!path << i);
            cur = trie[cur][!path];
        }
        else
        {
            ans |= path << i;
            cur = trie[cur][path];
        }
    }
    return ans;
}

// max(arr[i] ^ arr[j])
ll max_xor(const vector<ll> &arr)
{
    build(arr);
    ll ans = 0;
    for (ll num : arr)
    {
        ans = max(ans, num ^ f(num));
    }
    clear();
    return ans;
}

ll max_xor_hash(const vector<ll> &arr)
{
    ll max = LLONG_MIN;
    for (ll num : arr)
    {
        max = std::max(num, max);
    }
    ll ans = 0;
    high = 63 - __builtin_clzll(max); // max != 0

    set<ll> s;
    for (ll i = high; i >= 0; i--)
    {
        ll better = ans | (1LL << i); // expect
        s.clear();
        for (ll num : arr)
        {
            num = (num >> i) << i;
            s.insert(num);

            if (s.count(better ^ num))
            {
                ans = better;
                break;
            }
        }
    }
    return ans;
}

signed main()
{
    vector<ll> arr = {3, 10, 5, 25, 2, 8};
    // 5 (00101) ^ 25 (11001) = 28 (11100)
    cout << "array: {3, 10, 5, 25, 2, 8}" << endl;
    cout << "max xor pair value: " << max_xor(arr) << endl;
    cout << "expected value: 28" << endl;
    return 0;
}