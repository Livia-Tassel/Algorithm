#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <list>
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

// for the current subtree, the maximum gain from robbing the root node, and the maximum gain from not robbing the root node.
ll yes, no;

void f(node *root)
{
    if (root == nullptr)
    {
        yes = 0;
        no = 0;
    }
    else
    {
        ll y = root->data, n = 0;
        f(root->left);
        y += no;
        n += max(yes, no);

        f(root->right);
        y += no;
        n += max(yes, no);

        yes = y;
        no = n;
    }
}

ll rob(node *root)
{
    f(root);
    return max(yes, no);
}