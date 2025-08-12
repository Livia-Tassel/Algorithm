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

ll max_special_node(node *root)
{
    vector<node *> queue(MAXN);
    vector<ll> dex(MAXN);
    ll ans = 0;

    if (root != nullptr)
    {
        l = r = 0;
        queue[r] = root;
        dex[r++] = 1;

        while (l < r)
        {
            ll size = r - l;
            ans = max(ans, dex[r - 1] - dex[l] + 1);
            for (ll i = 0; i < size; i++)
            {
                node *cur = queue[l];
                ll s = dex[l++];

                if (cur->left != nullptr)
                {
                    queue[r] = cur->left;
                    dex[r++] = 2 * s;
                }
                if (cur->right != nullptr)
                {
                    queue[r] = cur->right;
                    dex[r++] = 2 * s + 1;
                }
            }
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
    //   4 null  6
    node *root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->right->right = new node(6);

    cout << max_special_node(root) << endl;

    delete root;
    return 0;
}
