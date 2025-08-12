#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <list>
#define ll long long
using namespace std;
const ll MAXN = 10001;
vector<node *> node_q(MAXN);
ll l, r;

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

bool complete_tree(node *root)
{
    if (root == nullptr)
    {
        return true;
    }

    l = r = 0;
    node_q[r++] = root;

    bool leaf = false; // complete node
    while (l < r)
    {
        node *cur = node_q[l++];

        if ((cur->left == nullptr && cur->right != nullptr) || (leaf && (cur->left != nullptr || cur->right != nullptr)))
        {
            return false;
        }

        if (cur->left != nullptr)
        {
            node_q[r++] = cur->left;
        }
        if (cur->right != nullptr)
        {
            node_q[r++] = cur->right;
        }

        if (cur->left == nullptr || cur->right == nullptr)
        {
            leaf = true;
        }
    }
}
