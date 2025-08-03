#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <cstdlib>

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
        cout << "deleting node: " << data << endl;
        delete left;
        delete right;
    }
};

// time O(n), space O(h)
// void preorder(node *root)
// {
//     if (root == nullptr)
//         return;

//     cout << root->data << " ";
//     preorder(root->left);
//     preorder(root->right);
// }

// void inorder(node *root)
// {
//     if (root == nullptr)
//         return;

//     inorder(root->left);
//     cout << root->data << " ";
//     inorder(root->right);
// }

// void postorder(node *root)
// {
//     if (root == nullptr)
//         return;

//     postorder(root->left);
//     postorder(root->right);
//     cout << root->data << " ";
// }

// time O(n), space O(h)
void preorder(node *root)
{
    if (root != nullptr)
    {
        stack<node *> s;
        s.push(root);

        while (!s.empty())
        {
            node *curr = s.top();
            s.pop();
            cout << curr->data << " ";

            if (curr->right != nullptr)
                s.push(curr->right);
            if (curr->left != nullptr)
                s.push(curr->left);
        }
    }
}

signed main()
{
    node *root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);

    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    // cout << "Inorder: ";
    // inorder(root);
    // cout << endl;

    // cout << "Postorder: ";
    // postorder(root);
    // cout << endl;

    delete root;

    root = nullptr;

    cout << "Program Finished." << endl;
    return 0;
}