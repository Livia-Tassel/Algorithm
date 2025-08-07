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

list<list<ll>> level_order(node *root)
{
    vector<node *> queue(MAXN);
    list<list<ll>> ans;

    if (root != nullptr)
    {
        l = r = 0;
        queue[r++] = root;

        while (l < r)
        {
            ll size = r - l;
            list<ll> lt;
            for (ll i = 0; i < size; i++)
            {
                node *cur = queue[l++];
                if (cur->left != nullptr)
                {
                    queue[r++] = cur->left;
                }
                if (cur->right != nullptr)
                {
                    queue[r++] = cur->right;
                }

                lt.push_back(cur->data);
            }
            ans.push_back(lt);
        }
    }

    return ans;
}

signed main()
{
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6
    node *root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->right->right = new node(6);

    cout << "performing level order traversal..." << endl;
    list<list<ll>> traversal_result = level_order(root);

    ll level = 0;
    for (const auto &level_list : traversal_result)
    {
        cout << "Level " << level++ << ": ";
        for (ll val : level_list)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    delete root;
    return 0;
}