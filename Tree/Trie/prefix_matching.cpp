#include <iostream>
#include <vector>
#include <string>
#include <memory>
#define ll long long
using namespace std;
const ll MAXN = 100001;
const ll S = 12; // 0~9, -, #
ll trie[MAXN][S], pass[MAXN], tail[MAXN];
ll cnt;

void build()
{
    cnt = 1;
}

ll path(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch == '-')
        return 10;
    if (ch == '#')
        return 11;
    return -1;
}

void insert(string word)
{
    ll cur = 1; // root
    pass[cur]++;
    for (char ch : word)
    {
        ll orient = path(ch);
        if (trie[cur][orient] == 0)
        {
            trie[cur][orient] = ++cnt;
        }
        cur = trie[cur][orient];
        pass[cur]++;
    }
    tail[cur]++;
}

ll count(string word)
{
    ll cur = 1;
    for (char ch : word)
    {
        ll orient = path(ch);
        if (trie[cur][orient] == 0)
        {
            return 0;
        }
        cur = trie[cur][orient];
    }
    return tail[cur];
}

ll pre(string prefix)
{
    ll cur = 1;
    for (char ch : prefix)
    {
        ll orient = path(ch);
        if (trie[cur][orient] == 0)
        {
            return 0;
        }
        cur = trie[cur][orient];
    }
    return pass[cur];
}

void erase(string word)
{
    if (count(word) != 0)
    {
        ll cur = 1;
        pass[cur]--;
        for (char ch : word)
        {
            ll orient = path(ch);
            if (--pass[trie[cur][orient]] == 0)
            {
                trie[cur][orient] = 0;
                return;
            }
            cur = trie[cur][orient];
        }
        tail[cur]--;
    }
}

void clear()
{
    for (ll i = 0; i <= cnt; i++)
    {
        memset(trie[i], 0, sizeof(trie[i]));
        tail[i] = 0;
        pass[i] = 0;
    }
}

// a
// [3, 7, 8, 0],   →  4, 1, -8   →  "4#1#-8#"
// [2, 4, -1],     →  2, -5      →  "2#-5#"
// [1, 5, 8, 3]    →  4, 3, -5   →  "4#3#-5#"
// b
// [0, 4],         →  4          →  "4#"        →  pre = 2
// [1, 3],         →  2          →  "2#"        →  pre = 1
// [1, 5, 8, 2]    →  4, 3, -6   →  "4#3#-6#"   →  pre = 0
vector<ll> prefix_arr(const vector<vector<ll>> &a, const vector<vector<ll>> &b)
{
    build();
    string s;
    for (const auto &aa : a)
    {
        s = "";
        for (ll i = 1; i < aa.size(); i++)
        {
            s += (to_string(aa[i] - aa[i - 1]) + "#");
        }
        if (!s.empty())
        {
            insert(s);
        }
    }

    vector<ll> ans;
    for (const auto &bb : b)
    {
        s = "";
        for (ll i = 1; i < bb.size(); i++)
        {
            s += (to_string(bb[i] - bb[i - 1]) + "#");
        }
        if (s.empty())
        {
            ans.push_back(0);
        }
        else
        {
            ans.push_back(pre(s));
        }
    }

    clear();
    return ans;
}

signed main()
{
    vector<vector<ll>> a = {
        {10, 20, 25, 23}, // "10#5#-2#"
        {10, 20, 25, 35}, // "10#5#10#"
        {10, 20, 15},     // "10#-5#"
        {0, 10},          // "10#"
        {100},            // ""
        {-5, -10, -15},   // "-5#-5#"
        {1, 2, 3, 4, 5}   // "1#1#1#1#"
    };

    vector<vector<ll>> b = {
        {0, 10},              // "10#"
        {5, 15, 20},          // "10#5#"
        {10, 20, 25, 23},     // "10#5#-2#"
        {100, 101, 102},      // "1#1#"
        {10, 20, 25, 35, 45}, // "10#5#10#10#"
        {50},                 // ""
        {0, 0, 0},            // "0#0#"
        {-2, -7, -12}         // "-5#-5#"
    };

    vector<ll> result = prefix_arr(a, b);
    return 0;
}