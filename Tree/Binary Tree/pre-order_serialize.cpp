#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <list>
#include <stdexcept>
#define ll long long
using namespace std;

struct node
{
    ll data;
    node *left;
    node *right;

    node(ll val) : data(val), left(nullptr), right(nullptr) {}

    ~node()
    {
        delete left;
        delete right;
    }
};

void sse(node *root, string &s)
{
    if (root == nullptr)
    {
        s += "#,";
    }
    else
    {
        ll val = root->data;
        s += (to_string(val) + ",");
        sse(root->left, s);
        sse(root->right, s);
    }
}

string serialize(node *root)
{
    string s;
    sse(root, s);
    return s;
}

ll cnt;
node *sde(vector<string> &vals)
{
    if (cnt >= vals.size())
    {
        return nullptr;
    }

    string cur = vals[cnt++];
    if (cur == "#")
    {
        return nullptr;
    }
    else
    {
        node *head = new node(stoll(cur));
        head->left = sde(vals);
        head->right = sde(vals);
        return head;
    }
}

node *deserialize(string s)
{
    // split the string with ','
    stringstream ss(s);
    string token;
    vector<string> vals;
    while (getline(ss, token, ','))
    {
        if (!token.empty())
        {
            vals.push_back(token);
        }
    }

    cnt = 0;
    return sde(vals);
}