#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#define ll long long
using namespace std;

struct node
{
    ll data;
    node *next;
    node(ll val) : data(val), next(nullptr) {}
};

bool palindrome(node *head)
{
    if (head == nullptr || head->next == nullptr)
        return true;

    node *slow = head, *fast = head;

    // 1 → 2 → 2 → 1

    //     ↑
    // 1 → 2 ← 2 ← 1
    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    // reverse
    // head → ... → slow ← ... ← prev
    node *prev = slow, *cur = prev->next, *next = nullptr;
    prev->next = nullptr;
    while (cur != nullptr)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    bool ans = true;
    node *left = head, *right = prev;
    while (left != nullptr && right != nullptr)
    {
        if (left->data != right->data)
        {
            ans = false;
            break;
        }
        left = left->next;
        right = right->next;
    }

    // restore the original list
    cur = prev->next;
    prev->next = nullptr;
    next = nullptr;
    while (cur != nullptr)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return ans;
}

void delete_list(node *head)
{
    while (head != nullptr)
    {
        node *temp = head;
        head = head->next;
        delete temp;
    }
}

signed main()
{
    node *head = new node(1);
    head->next = new node(2);
    head->next->next = new node(2);
    head->next->next->next = new node(3);

    palindrome(head) ? cout << "YES" << endl
                     : cout << "NO" << endl;

    node *cur = head;
    while (cur != nullptr)
    {
        cout << cur->data << " ";
        cur = cur->next;
    }
    
    delete_list(head);
    return 0;
}