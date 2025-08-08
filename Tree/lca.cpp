#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
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

node *lca(node *root, node *p, node *q)
{
    if (root == nullptr || root == p || root == q)
    {
        return root;
    }

    node *l = lca(root->left, p, q);
    node *r = lca(root->right, p, q);

    if (l != nullptr && r != nullptr)
    {
        return root;
    }
    if (l == nullptr && r == nullptr)
    {
        return nullptr;
    }

    return l != nullptr ? l : r;
}

node *search_tree_lca(node *root, node *p, node *q)
{
    while (root != p && root != q)
    {
        if (min(p->data, q->data) < root->data && max(p->data, q->data) > root->data)
        {
            break;
        }
        root = root->data < min(p->data, q->data) ? root->right : root->left;
    }
    return root;
}

node *build_tree()
{
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    //  /
    // 6
    node *root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->left->left->left = new node(6);
    return root;
}

signed main()
{
    node *root = build_tree();

    delete root;
    return 0;
}