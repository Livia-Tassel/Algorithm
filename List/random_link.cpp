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
    node *random;
    node(ll val) : data(val), next(nullptr), random(nullptr) {}
};

// copy a linked list with random pointers
node *linked_list(node *head)
{
    if (head == nullptr)
        return nullptr;

    node *cur = head, *next = nullptr;
    // 1 → 2 → 3 → null
    // 1 → 1' → 2 → 2' → 3 → 3' → null
    while (cur != nullptr)
    {
        next = cur->next;
        cur->next = new node(cur->data);
        cur->next->next = next;
        cur = next;
    }

    // random pointers
    cur = head;
    node *copy = nullptr;
    while (cur != nullptr)
    {
        copy = cur->next;
        copy->random = (cur->random != nullptr ? cur->random->next : nullptr);
        cur = copy->next;
    }

    // 1 → 2 → 3 → null
    // 1' → 2' → 3' → null
    node *ans = head->next;
    cur = head;
    while (cur != nullptr)
    {
        next = cur->next->next;
        copy = cur->next;
        cur->next = next;
        copy->next = (next != nullptr ? next->next : nullptr);
        cur = next;
    }

    return ans;
}

void delete_linked_list(node *head)
{
    node *cur = head;
    while (cur != nullptr)
    {
        node *next_node = cur->next;
        delete cur;
        cur = next_node;
    }
}

signed main()
{
    node *head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->random = head->next->next;       // random pointer to node 3
    head->next->random = head;             // random pointer to node 1
    head->next->next->random = head->next; // random pointer to node 2
    head->next->next->next->random = nullptr;

    node *copy = linked_list(head);
    cout << "original list: " << endl;
    for (node *cur = head; cur != nullptr; cur = cur->next)
    {
        cout << "Value: " << cur->data << ", Random: " << (cur->random != nullptr ? cur->random->data : -1) << endl;
    }

    cout << "copied list: " << endl;
    for (node *cur = copy; cur != nullptr; cur = cur->next)
    {
        cout << "Value: " << cur->data << ", Random: " << (cur->random != nullptr ? cur->random->data : -1) << endl;
    }

    // cleanup
    delete_linked_list(head);
    delete_linked_list(copy);
    return 0;
}