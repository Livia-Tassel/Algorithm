#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <list>
#define ll long long
using namespace std;
ll goal;

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

void process(node *cur, ll sum, list<ll> &path, list<list<ll>> &ans)
{
    path.push_back(cur->data);
    sum += cur->data;

    if (cur->left == nullptr && cur->right == nullptr)
    {
        if (sum == goal)
        {
            ans.push_back(path);
        }
    }
    else
    {
        if (cur->left != nullptr)
        {
            process(cur->left, sum, path, ans);
        }
        if (cur->right != nullptr)
        {
            process(cur->right, sum, path, ans);
        }
    }

    path.pop_back();
}

list<list<ll>> path_sum(node *root, ll target)
{
    goal = target;
    list<list<ll>> ans;
    if (root != nullptr)
    {
        list<ll> path;
        process(root, 0, path, ans);
    }
    return ans;
}

void print_paths(const list<list<ll>> &paths)
{
    if (paths.empty())
    {
        cout << "no valid paths found." << endl;
        return;
    }
    for (const auto &path : paths)
    {
        cout << "[ ";
        for (ll val : path)
        {
            cout << val << " ";
        }
        cout << "]" << endl;
    }
}

node *build_test_tree()
{
    //       5
    //      / \
    //     4   8
    //    /   / \
    //   11  13  4
    //  /  \    / \
    // 7    2  5   1
    node *root = new node(5);
    root->left = new node(4);
    root->right = new node(8);
    root->left->left = new node(11);
    root->left->left->left = new node(7);
    root->left->left->right = new node(2);
    root->right->left = new node(13);
    root->right->right = new node(4);
    root->right->right->left = new node(5);
    root->right->right->right = new node(1);
    return root;
}

signed main()
{
    node *root = build_test_tree();
    list<list<ll>> ans = path_sum(root, 18);
    print_paths(ans);

    delete root;
    return 0;
}