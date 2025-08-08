#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <sstream>
#include <queue>
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

const ll MAXN = 10001;
vector<node *> node_q(MAXN);
ll l, r;

string serialize(node *root)
{
    if (root == nullptr)
    {
        return "#,";
    }

    string s = "";
    l = r = 0;

    node_q[r++] = root;
    s += (to_string(root->data) + ",");

    while (l < r)
    {
        ll size = r - l;
        for (ll i = 0; i < size; i++)
        {
            node *cur = node_q[l++];

            if (cur->left != nullptr)
            {
                node_q[r++] = cur->left;
                s += (to_string(cur->left->data) + ",");
            }
            else
            {
                s += "#,";
            }

            if (cur->right != nullptr)
            {
                node_q[r++] = cur->right;
                s += (to_string(cur->right->data) + ",");
            }
            else
            {
                s += "#,";
            }
        }
    }
    return s;
}

node *deserialize(string s)
{
    if (s == "#,")
    {
        return nullptr;
    }

    stringstream ss(s);
    string token;
    vector<string> vals;
    while (getline(ss, token, ','))
    {
        if (!token.empty())
        {
            vals.push_back(token);
        }
    }

    if (vals.empty())
    {
        return nullptr;
    }

    ll cnt = 0;
    node *root = new node(stoll(vals[cnt++]));

    l = r = 0;
    node_q[r++] = root;

    while (l < r)
    {
        node *cur = node_q[l++];

        if (cnt < vals.size() && vals[cnt] != "#")
        {
            cur->left = new node(stoll(vals[cnt]));
            node_q[r++] = cur->left;
        }
        cnt++;

        if (cnt < vals.size() && vals[cnt] != "#")
        {
            cur->right = new node(stoll(vals[cnt]));
            node_q[r++] = cur->right;
        }
        cnt++;
    }
    return root;
}

signed main()
{
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    node *root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    // root->left->left = new node(4);
    root->left->right = new node(5);

    string serialized_tree = serialize(root);
    cout << "serialized string: " << serialized_tree << endl;

    node *new_root = deserialize(serialized_tree);

    string reserialized_tree = serialize(new_root);
    cout << "deserialized and reserialized string: " << reserialized_tree << endl;

    if (serialized_tree == reserialized_tree)
    {
        cout << "\nserialization and deserialization successful!" << endl;
    }
    else
    {
        cout << "\nerror: The trees do not match." << endl;
    }

    delete root;
    delete new_root;

    return 0;
}