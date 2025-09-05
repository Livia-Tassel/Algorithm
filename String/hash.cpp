#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
#include <unordered_set>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;
using vvc = vector<vector<char>>;
using vs = vector<string>;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 5;
const ll base = 499;
const ll maxn = 10005;

// 赌狗的胜利
// '0' → 1
// '1' → 2
// ...
// '9' → 10
// 'A' → 11
// 'B' → 12
// ...
// 'a' → 37
// ...
ull v(char c)
{
    if (c > 47 && c < 58)
    {
        return c - '0' + 1;
    }
    else if (c > 64 && c < 91)
    {
        return c - 'A' + 11;
    }
    else
    {
        return c - 'a' + 37;
    }
}
ull value(string s)
{
    ull ans = v(s[0]);
    for (ull i = 1; i < s.length(); i++)
    {
        ans = ans * base + v(s[i]);
    }
    return ans;
}

// s of digits, return the number of unique non-empty substrings where each digit appears with the same frequency.
ull frequency(string &str)
{
    ull n = str.length();
    unordered_set<ull> s;
    vl cnt(10);

    for (ull i = 0; i < n; i++)
    {
        fill(cnt.begin(), cnt.end(), 0);
        ull hashCode = 0;
        ull curVal = 0, maxCnt = 0, maxCntKinds = 0, allKinds = 0;

        for (ull j = i; j < n; j++)
        {
            curVal = str[j] - '0';
            hashCode = hashCode * base + curVal + 1;

            if (cnt[curVal] == 0)
            {
                allKinds++;
            }
            cnt[curVal]++;

            if (cnt[curVal] > maxCnt)
            {
                maxCnt = cnt[curVal];
                maxCntKinds = 1;
            }
            else if (cnt[curVal] == maxCnt)
            {
                maxCntKinds++;
            }

            if (maxCntKinds == allKinds)
            {
                s.insert(hashCode);
            }
        }
    }

    return s.size();
}

// substring hash
vl bp(maxn), ph(maxn);
char s[maxn]; // string s
void build(string s, ull n)
{
    bp[0] = 1;
    for (ull i = 1; i < n; i++)
    {
        bp[i] = base * bp[i - 1];
    }
    ph[0] = s[0] - 'a' + 1;
    for (ull i = 1; i < n; i++)
    {
        ph[i] = base * ph[i - 1] + s[i] - 'a' + 1;
    }
}
ull subh(ull l, ull r)
{
    ull ans = ph[r];
    if (l > 0)
    {
        ans -= ph[l - 1] * bp[r - l + 1];
    }
    return ans;
}

// the minimum number of times to repeat a so that b becomes a substring of the repeated string.
ull repeated(string a, string b)
{
    ull n = a.length(), m = b.length();
    ull k = (m + n - 1) / n;

    // k+1
    ull len = 0;
    for (ull i = 0; i < k + 1; i++)
    {
        for (ull j = 0; j < n; j++)
        {
            s[len++] = a[j];
        }
    }

    // build(len);
    ull hb = b[0] - 'a' + 1;
    for (ull i = 1; i < m; i++)
    {
        hb = base * hb + b[i] - 'a' + 1;
    }

    for (ull l = 0, r = m - 1; r < len; l++, r++)
    {
        if (hb == subh(l, r))
        {
            return r < n * k ? k : k + 1;
        }
    }
    return -1;
}

// array of words where all words have the same length, concatenated substring is a substring formed by concatenating all the words from the array in any order, find all starting indices of such concatenated substrings in s.
vl substring(string s, vs &rds)
{
    vl ans;
    if (s.empty() || rds.empty() || rds[0].empty())
    {
        return ans;
    }

    unordered_map<ull, ll> mp;
    for (string &rd : rds)
    {
        ull hd = value(rd);
        mp[hd]++;
    }

    ll n = s.length();
    build(s, n);

    ll len = rds[0].size();
    ll num = rds.size();
    ll allen = num * len;

    for (ll init = 0; init < len && init + allen < n + 1; init++)
    {
        unordered_map<ull, ll> slid;
        ll debt = num;

        for (ll i = 0; i < num; i++)
        {
            ull ch = subh(init + i * len, init + (i + 1) * len);
            slid[ch]++;
            if (mp.count(ch) && slid[ch] < mp[ch] + 1)
            {
                debt--;
            }
        }

        if (debt == 0)
        {
            ans.push_back(init);
        }

        for (ll l1 = init; l1 + allen + len < n + 1; l1 += len)
        {
            ll r1 = l1 + len;
            ll l2 = l1 + allen;
            ll r2 = l2 + len;

            ull oh = subh(l1, r1);
            if (mp.count(oh) && slid[oh] < mp[oh] + 1)
            {
                debt++;
            }
            slid[oh]--;

            ull ih = subh(l2, r2);
            slid[ih]++;
            if (mp.count(ih) && slid[ih] < mp[ih] + 1)
            {
                debt--;
            }

            if (debt == 0)
            {
                ans.push_back(r1);
            }
        }
    }
    return ans;
}

// substring of s matches p if they have the same length and their characters differ by at most k positions, find the number of substrings in s that match p.
vl bp(maxn), phs(maxn), php(maxn);
void build(string s, ull n, string p, ll m)
{
    bp[0] = 1;
    for (ull i = 1; i < n; i++)
    {
        bp[i] = base * bp[i - 1];
    }

    phs[0] = s[0] - 'a' + 1;
    for (ull i = 1; i < n; i++)
    {
        phs[i] = base * phs[i - 1] + s[i] - 'a' + 1;
    }
    php[0] = p[0] - 'a' + 1;
    for (ull i = 1; i < m; i++)
    {
        php[i] = base * php[i - 1] + p[i] - 'a' + 1;
    }
}
ull subh(vl &ph, ull l, ull r)
{
    ull ans = ph[r];
    if (l > 0)
    {
        ans -= ph[l - 1] * bp[r - l + 1];
    }
    return ans;
}
bool same(ll ls, ll lp, ll len)
{
    return subh(phs, ls, ls + len - 1) == subh(php, lp, lp + len - 1);
}
// s[l,r], p[0,m-1]
bool check(ll ls, ll rs, ll k)
{
    ll diff = 0;
    ll lp = 0;

    while (ls < rs + 1 && diff < k + 1)
    {
        ll l = 1, r = rs - ls + 1;
        ll m, len = 0;
        // search max length
        while (l < r + 1)
        {
            m = (l + r) / 2;
            if (same(ls, lp, m))
            {
                len = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        if (ls + len < rs + 1)
        {
            diff++;
        }
        ls += len + 1;
        lp += len + 1;
    }

    return diff < k + 1;
}
ll match(string s, string p, ll k)
{
    ll n = s.length(), m = p.length();
    if (n < m)
    {
        return 0;
    }
    build(s, n, p, m);
    ll ans = 0;
    for (ll i = 0; i < n - m + 1; i++)
    {
        if (check(i, i + m - 1, k))
        {
            ans++;
        }
    }
    return ans;
}