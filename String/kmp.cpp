#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <list>
#include <set>
#include <stack>
#include <map>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vpll = vector<pair<ll, ll>>;
using vs = vector<string>;

// nexp array represents the length of the longest prefix of the string up to the current position (not including the current character) that is also a suffix of that same string (not including the whole string).
vl nexp(100001);
void f(string s, ll m)
{
    nexp[0] = -1, nexp[1] = 0;
    // s != ""
    if (m < 2)
        return;
    ll i = 2, cn = 0;
    while (i < m + 1)
    {
        if (s[i - 1] == s[cn])
        {
            nexp[i++] = ++cn;
        }
        else if (cn > 0)
        {
            cn = nexp[cn];
        }
        else
        {
            nexp[i++] = 0;
        }
    }
}
// n + m
ll kmp(string s, string tar)
{
    ll n = s.length(), m = tar.length();
    ll x = 0, y = 0;
    while (x < n && y < m)
    {
        if (s[x] == tar[y])
        {
            x++, y++;
        }
        else if (y == 0)
        {
            x++;
        }
        else
        {
            y = nexp[y];
        }
    }

    return y != m ? -1 : x - y;
}

// binary trees, root and subRoot, check if root contains a subtree that has the same structure and node values as subRoot.
struct node
{
    node *left;
    node *right;
    ll val;
};

void f(node *root, string &s)
{
    if (root == nullptr)
    {
        s += "#,";
    }
    else
    {
        ll v = root->val;
        s += (to_string(v) + ",");
        f(root->left, s);
        f(root->right, s);
    }
}
string serialize(node *root)
{
    string s;
    f(root, s);
    return s;
}
bool subtree(node *root, node *sub)
{
    if (root != nullptr && sub != nullptr)
    {
        string r = ',' + serialize(root);
        string s = ',' + serialize(sub);
        return kmp(r, s) != -1;
    }

    return sub == nullptr;
}

// string s which is formed by repeating a core unit, at least two repetitions, but the last one might be incomplete, find the length of the shortest repeating unit of s.
// U U U U l
// max(nexp) = (k-1)U + l
ll unit(string s)
{
    ll n = s.length();
    f(s, n);
    return n - nexp[n];
}

// string s and a pattern string tar, repeatedly remove the leftmost occurrence of tar from s until s no longer contains tar, return the final string.
void remove(string s, string tar)
{
    ll n = s.length(), m = tar.length(), x = 0, y = 0;
    vpll st(n);
    ll top = 0;
    f(tar, m);

    while (x < n)
    {
        if (s[x] == tar[y])
        {
            st[top].first = x++;
            st[top++].second = y++;
        }
        else if (y == 0)
        {
            st[top].first = x++;
            st[top++].second = -1;
        }
        else
        {
            y = nexp[y];
        }

        // x a b c b c c y a b c a
        // a b c
        //-1 0 0
        if (y == m)
        {
            top -= m;
            y = top > 0 ? (st[top - 1].second + 1) : 0;
        }
    }

    for (ll i = 0; i < top; i++)
    {
        cout << s[st[i].first];
    }
}

// binary tree and a linked list, determine if there is a downward path in the tree whose sequence of values is identical to that of the linked list.
struct ln
{
    ll val;
    ln *next;
};
void f(vl &s, ll m)
{
    nexp[0] = -1, nexp[1] = 0;
    // s != ""
    if (m < 2)
        return;
    ll i = 2, cn = 0;
    while (i < m + 1)
    {
        if (s[i - 1] == s[cn])
        {
            nexp[i++] = ++cn;
        }
        else if (cn > 0)
        {
            cn = nexp[cn];
        }
        else
        {
            nexp[i++] = 0;
        }
    }
}
bool find(vl &tar, vl &nexp, node *cur, ll i, ll m)
{
    if (i == m)
        return true;
    if (cur == nullptr)
        return false;

    while (i > -1 && cur->val != tar[i])
    {
        i = nexp[i];
    }
    return find(tar, nexp, cur->left, i + 1, m) || find(tar, nexp, cur->right, i + 1, m);
}
// n + m
bool subpath(ln *head, node *root)
{
    ll m = 0;
    ln *t = head;
    while (t != nullptr)
    {
        m++;
        t = t->next;
    }

    vl tar(m);
    m = 0;
    while (head != nullptr)
    {
        tar[m++] = head->val;
        head = head->next;
    }

    f(tar, m);
    return find(tar, nexp, root, 0, m);
}

// st and se of length n, and a string evil, "good string" is a string of length n that is lexicographically greater than or equal to st, less than or equal to se, and does not contain evil as a substring, return the number of good strings.
ll jump(char pick, string evil, ll j)
{
    while (j > -1 && pick != evil[j])
    {
        j = nexp[j];
    }
    return j;
}
ll solve(ll n, ll m, string s, string evil, ll i, ll j, ll free)
{
    if (j == m)
        return 0;
    if (i == n)
        return 1;

    if (dp[i][j][free] != -1)
    {
        return dp[i][j][free];
    }

    char ch = s[i];
    ll ans = 0;
    if (!free)
    {
        for (char pick = 'a'; pick < ch; pick++)
        {
            ans = (ans + solve(n, m, s, evil, i + 1, jump(pick, evil, j) + 1, 1)) % mod;
        }
        ans = (ans + solve(n, m, s, evil, i + 1, jump(ch, evil, j) + 1, 0)) % mod;
    }
    else
    {
        for (char pick = 'a'; pick - 1 < 'z'; pick++)
        {
            ans = (ans + solve(n, m, s, evil, i + 1, jump(pick, evil, j) + 1, 1)) % mod;
        }
    }

    dp[i][j][free] = ans;
    return ans;
}
ll dp[501][501][2];
void clear(ll n, ll m)
{
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
        }
    }
}
const ll mod = 1e9 + 7;
ll evil(ll n, string st, string se, string evil)
{
    ll m = evil.length();
    f(evil, m);
    clear(n, m);
    ll ans = solve(n, m, se, evil, 0, 0, 0);
    clear(n, m);
    ans = (ans - solve(n, m, st, evil, 0, 0, 0) + mod) % mod;

    if (kmp(st, evil) == -1)
    {
        ans = (ans + 1) % mod;
    }
    return ans;
}
