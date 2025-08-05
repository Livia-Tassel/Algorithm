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

// return the entrance node of a cyclic linked list.
node *cyclic_list(node *head)
{
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
    {
        return nullptr;
    }

    node *slow = head->next, *fast = head->next->next;
    while (slow != fast)
    {
        if (fast->next == nullptr || fast->next->next == nullptr)
        {
            return nullptr;
        }
        slow = slow->next;
        fast = fast->next->next;
    }

    fast = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    return fast;
}

void delete_linked_list(node *head)
{
    node *current = head;
    while (current != nullptr)
    {
        node *next_node = current->next;
        delete current;
        current = next_node;
    }
}

void delete_cyclic_list(node *head)
{
    if (head == nullptr)
        return;

    node *entrance = cyclic_list(head);
    if (entrance == nullptr)
    {
        delete_linked_list(head);
        return;
    }

    node *tail_of_cycle = entrance;
    while (tail_of_cycle->next != entrance)
    {
        tail_of_cycle = tail_of_cycle->next;
    }
    tail_of_cycle->next = nullptr;

    delete_linked_list(head);
}

signed main()
{
    node *head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = new node(5);
    head->next->next->next->next->next = head->next->next;

    node *entrance = cyclic_list(head);
    if (entrance != nullptr)
    {
        cout << "cycle entrance found at node with value: " << entrance->data << endl;
    }
    else
    {
        cout << "no cycle found." << endl;
    }

    delete_cyclic_list(head);
    cout << "cyclic list successfully deleted." << endl;

    return 0;
}
