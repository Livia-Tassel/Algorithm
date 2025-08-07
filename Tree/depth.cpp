#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <list>
#define ll long long
using namespace std;
const ll MAXN = 10001;
ll l, r;

struct node
{
    ll data;
    node *left;
    node *right;

    node(ll val) : data(val), left(nullptr), right(nullptr) {}

    ~node()
    {
        cout << "deleting node: " << data << endl;
        delete left;
        delete right;
    }
};

ll max_depth(node *root)
{
    return root != nullptr ? max(max_depth(root->left), max_depth(root->right)) + 1 : 0;
}

ll min_depth(node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (root->left == nullptr && root->right == nullptr)
    {
        return 1;
    }

    ll min_l = LLONG_MAX, min_r = LLONG_MAX;
    if (root->left != nullptr)
    {
        min_l = min_depth(root->left);
    }
    if (root->right != nullptr)
    {
        min_r = min_depth(root->right);
    }
    return min(min_l, min_r) + 1;
}

signed main()
{
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4 null  6
    node *root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    // root->right->right = new node(6);

    cout << max_depth(root) << endl;
    cout << min_depth(root) << endl;

    delete root;
    return 0;
}
