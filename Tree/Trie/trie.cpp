#include <iostream>
#include <vector>
#include <string>
#include <memory>
#define ll long long
using namespace std;

// struct trie
// {
//     struct node
//     {
//         ll pass, end;
//         vector<node *> next;

//         node() : pass(0), end(0), next(26, nullptr) {}
//     };

//     node *root;

//     trie() : root(new node()) {}

//     ~trie()
//     {
//         clear(root);
//     }

// private:
//     void clear(node *cur)
//     {
//         if (cur == nullptr)
//             return;
//         for (ll i = 0; i < 26; ++i)
//         {
//             if (cur->next[i] != nullptr)
//             {
//                 clear(cur->next[i]);
//             }
//         }
//         delete cur;
//     }

// public:
//     void insert(string word)
//     {
//         node *cur = root;
//         cur->pass++;
//         for (char ch : word)
//         {
//             ll orient = ch - 'a';
//             if (cur->next[orient] == nullptr)
//             {
//                 cur->next[orient] = new node();
//             }
//             cur = cur->next[orient];
//             cur->pass++;
//         }
//         cur->end++;
//     }

//     ll count(string word)
//     {
//         node *cur = root;
//         for (char ch : word)
//         {
//             ll orient = ch - 'a';
//             if (cur->next[orient] == nullptr)
//             {
//                 return 0;
//             }
//             cur = cur->next[orient];
//         }
//         return cur->end;
//     }

//     ll pre(string prefix)
//     {
//         node *cur = root;
//         for (char ch : prefix)
//         {
//             ll orient = ch - 'a';
//             if (cur->next[orient] == nullptr)
//             {
//                 return 0;
//             }
//             cur = cur->next[orient];
//         }
//         return cur->pass;
//     }

//     void erase(string word)
//     {
//         if (count(word) > 0)
//         {
//             node *cur = root;
//             cur->pass--;
//             for (char ch : word)
//             {
//                 ll orient = ch - 'a';
//                 cur = cur->next[orient];
//                 cur->pass--;
//             }
//             cur->end--;
//         }
//     }
// };

const ll MAXN = 100001;
const ll S = 26;
ll trie[MAXN][S], pass[MAXN], tail[MAXN];
ll cnt;

void build()
{
    cnt = 1;
}

void insert(string word)
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
    tail[cur]++;
}

ll count(string word)
{
    ll cur = 1;
    for (char ch : word)
    {
        ll orient = ch - 'a';
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
        ll orient = ch - 'a';
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
            ll orient = ch - 'a';
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

signed main()
{
    build();

    vector<string> words = {"apple", "apply", "app", "ape", "ace", "hello"};
    for (const string &word : words)
    {
        cout << "inserting: " << word << endl;
        insert(word);
    }

    return 0;
}