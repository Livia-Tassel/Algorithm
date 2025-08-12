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

ll most_left(node *cur, ll level)
{
    while (cur != nullptr)
    {
        level++;
        cur = cur->left;
    }
    return level - 1;
}

ll solve(node *cur, ll level, ll h)
{
    if (level == h)
    {
        return 1;
    }

    if (most_left(cur->right, level + 1) == h)
    {
        return (1 << (h - level)) + solve(cur->right, level + 1, h);
    }
    else
    {
        return (1 << (h - level - 1)) + solve(cur->left, level + 1, h);
    }
}

ll count_node(node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return solve(root, 1, most_left(root, 1));
}

signed main()
{
    //            1
    //           / \
    //          2   3
    //         / \ / \
    //        4  5 6  7
    node *perfect_root = new node(1);
    perfect_root->left = new node(2);
    perfect_root->right = new node(3);
    perfect_root->left->left = new node(4);
    perfect_root->left->right = new node(5);
    perfect_root->right->left = new node(6);
    perfect_root->right->right = new node(7);

    ll perfect_count = count_node(perfect_root);
    cout << (perfect_count == 7 ? "Result: Pass" : "Result: Fail") << endl;
    delete perfect_root;

    cout << "\n----------------------------------------\n"
         << endl;

    //            1
    //           / \
    //          2   3
    //         / \
    //        4   5
    node *complete_root = new node(1);
    complete_root->left = new node(2);
    complete_root->right = new node(3);
    complete_root->left->left = new node(4);
    complete_root->left->right = new node(5);

    ll complete_count = count_node(complete_root);
    cout << (complete_count == 5 ? "Result: Pass" : "Result: Fail") << endl;
    delete complete_root;

    return 0;
}