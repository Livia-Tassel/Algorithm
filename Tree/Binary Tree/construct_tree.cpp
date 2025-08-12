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

const ll MAXN = 10001;
vector<ll> pre(MAXN), mid(MAXN);
map<ll, ll> mp;

// Construct the Binary Tree from Pre-order and In-order Traversals.
node *build_tree(ll pre_l, ll pre_r, ll mid_l, ll mid_r)
{
    if (pre_l > pre_r || mid_l > mid_r)
    {
        return nullptr;
    }

    node *root = new node(pre[pre_l]);
    if (pre_l == pre_r)
    {
        return root;
    }

    ll dex = mp[root->data];
    ll len = dex - mid_l;

    root->left = build_tree(pre_l + 1, pre_l + len, mid_l, dex - 1);
    root->right = build_tree(pre_l + len + 1, pre_r, dex + 1, mid_r);

    return root;
}

void preorder_traversal(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->data << " ";
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void inorder_traversal(node *root)
{
    if (root == nullptr)
    {
        return;
    }
    inorder_traversal(root->left);
    cout << root->data << " ";
    inorder_traversal(root->right);
}

signed main()
{
    ll n;
    cin >> n;

    for (ll i = 0; i < n; i++)
    {
        cin >> pre[i];
    }

    for (ll i = 0; i < n; i++)
    {
        cin >> mid[i];
        mp[mid[i]] = i;
    }

    node *root = build_tree(0, n - 1, 0, n - 1);

    preorder_traversal(root);
    cout << endl;
    inorder_traversal(root);
    cout << endl;

    delete root;
    return 0;
}