#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <bit>
#include <set>
#include <list>
#define ll long long
using namespace std;
const ll MAXN = 100001;
const ll S = 26;
ll trie[MAXN][S], pass[MAXN];
string tail[MAXN];
ll cnt;

void build(const vector<string> &words)
{
    cnt = 1;
    for (string word : words)
    {
        ll cur = 1; // root
        pass[cur]++;
        for (char ch : word)
        {
            ll orient = ch - 'a';
            if (trie[cur][orient] == 0)
            {
                trie[cur][orient] = ++cnt;
            }
            cur = trie[cur][orient];
            pass[cur]++;
        }
        tail[cur] = word;
    }
}

void clear()
{
    for (ll i = 0; i <= cnt; i++)
    {
        memset(trie[i], 0, sizeof(trie[i]));
        tail[i] = "";
        pass[i] = 0;
    }
}

ll dfs(vector<vector<char>> &board, ll i, ll j, ll cur, list<string> &ans)
{
    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] == 0)
    {
        return 0;
    }

    char tmp = board[i][j];
    ll path = tmp - 'a';
    cur = trie[cur][path];
    if (pass[cur] == 0) // no rood (cur = 0); exist road but pass[cur] = 0, means the previous process has already collected all the words from this point onwards.
    {
        return 0;
    }

    ll sum = 0;
    if (tail[cur] != "")
    {
        sum++;
        ans.push_back(tail[cur]);
        tail[cur] = "";
    }

    board[i][j] = 0;
    sum += dfs(board, i - 1, j, cur, ans);
    sum += dfs(board, i + 1, j, cur, ans);
    sum += dfs(board, i, j - 1, cur, ans);
    sum += dfs(board, i, j + 1, cur, ans);

    pass[cur] -= sum;
    board[i][j] = tmp;
    return sum;
}

// b c t
// a f k
// e c c
// search: "abc", "bce", "fkt"
list<string> pair_match(vector<vector<char>> &board, const vector<string> &words)
{
    build(words);
    list<string> ans;

    for (ll i = 0; i < board.size(); i++)
    {
        for (ll j = 0; j < board[0].size(); j++)
        {
            dfs(board, i, j, 1, ans);
        }
    }
    return ans;
}

signed main()
{
    vector<vector<char>> board = {
        {'a', 'b', 'c'},
        {'a', 'e', 'd'},
        {'a', 'f', 'g'}};
    vector<string> words = {"eaafg", "aed", "aabc", "febcdgf"};

    list<string> result = pair_match(board, words);

    cout << "found words:" << endl;
    for (const string &s : result)
    {
        cout << s << endl;
    }
    return 0;
}