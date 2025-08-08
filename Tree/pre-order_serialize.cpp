#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <list>
#include <stdexcept>
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

void solve_serialize(node *root, string &s)
{
    if (root == nullptr)
    {
        s += "#,";
    }
    else
    {
        ll val = root->data;
        s += (to_string(val) + ",");
        solve_serialize(root->left, s);
        solve_serialize(root->right, s);
    }
}

string serialize(node *root)
{
    string s;
    solve_serialize(root, s);
    return s;
}

ll cnt;
node *solve_deserialize(vector<string> &vals)
{
    if (cnt >= vals.size())
    {
        return nullptr;
    }

    string cur = vals[cnt++];
    if (cur == "#")
    {
        return nullptr;
    }
    else
    {
        node *head = new node(stoll(cur));
        head->left = solve_deserialize(vals);
        head->right = solve_deserialize(vals);
        return head;
    }
}

node *deserialize(string s)
{
    // split the string with ','
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

    cnt = 0;
    return solve_deserialize(vals);
}

signed main()
{
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   #
    //  / \
    // #   #
    node *root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
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