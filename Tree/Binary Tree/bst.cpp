#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <list>
#define ll long long
using namespace std;
ll gmin, gmax;

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

bool bst(node *root)
{
    if (root == nullptr)
    {
        gmin = LLONG_MAX;
        gmax = LLONG_MIN;
        return true;
    }

    bool lok = bst(root->left);
    ll lmin = gmin, lmax = gmax;
    bool rok = bst(root->right);
    ll rmin = gmin, rmax = gmax;

    gmin = min(min(lmin, rmin), root->data);
    gmax = max(max(lmax, rmax), root->data);

    return lok && rok && lmax < root->data && root->data < rmin;
}

node *trim_bst(node *cur, ll low, ll high)
{
    if (cur == nullptr)
    {
        return nullptr;
    }

    if (cur->data < low)
    {
        return trim_bst(cur->right, low, high);
    }
    if (cur->data > high)
    {
        return trim_bst(cur->left, low, high);
    }

    cur->left = trim_bst(cur->left, low, high);
    cur->right = trim_bst(cur->right, low, high);
    return;
}