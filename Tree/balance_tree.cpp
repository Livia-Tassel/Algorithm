#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <list>
#define ll long long
using namespace std;
bool balance;

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

ll height(node *cur)
{
    if (!balance || cur == nullptr)
    {
        return 0;
    }

    ll lh = height(cur->left);
    ll rh = height(cur->right);

    if (abs(lh - rh) > 1)
    {
        balance = false;
    }
    
    return max(lh, rh) + 1;
}

bool balance_tree(node *root)
{
    balance = true;
    height(root);
    return balance;
}
