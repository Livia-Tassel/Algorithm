#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#define ll long long
using namespace std;

// single linked list node
struct single_node
{
    ll data;
    single_node *next;
    single_node(ll val) : data(val), next(nullptr) {}
};

// double linked list node
struct double_node
{
    ll data;
    double_node *next;
    double_node *prev;
    double_node(ll val) : data(val), next(nullptr), prev(nullptr) {}
};

// reverse a single linked list
single_node *reverse_list(single_node *head)
{
    single_node *prev = nullptr;
    single_node *next = nullptr;
    while (head != nullptr)
    {
        // prev will be linked by head, next := head
        next = head->next; // next go along the list
        head->next = prev; // head -> prev
        prev = head;       // prev go along the list
        head = next;       // head go along the list
    }
    return prev;
}

// reverse a double linked list
double_node *reverse_doubly_list(double_node *head)
{
    double_node *prev = nullptr;
    double_node *next = nullptr;
    while (head != nullptr)
    {
        // prev will be linked by head, next := head
        next = head->next; // next go along the list
        head->next = prev; // head -> prev
        head->prev = next; // head -> next
        prev = head;       // prev go along the list
        head = next;       // head go along the list
    }
    return prev;
}

// merge two sorted single linked lists
single_node *merge_sorted_lists(single_node *l1, single_node *l2)
{
    if (l1 == nullptr || l2 == nullptr)
        return l1 ? l1 : l2;

    single_node *head = l1->data <= l2->data ? l1 : l2;
    single_node *cur_1 = head->next;
    single_node *cur_2 = head == l1 ? l2 : l1;
    single_node *temp = head;

    while (cur_1 && cur_2)
    {
        if (cur_1->data <= cur_2->data)
        {
            temp->next = cur_1;
            cur_1 = cur_1->next;
        }
        else
        {
            temp->next = cur_2;
            cur_2 = cur_2->next;
        }
        temp = temp->next;
    }
    temp->next = (cur_1 ? cur_1 : cur_2);
    return head;
}

signed main()
{
    // 1 -> 3 -> 5
    single_node *l1 = new single_node(1);
    l1->next = new single_node(3);
    l1->next->next = new single_node(5);

    // 2 -> 4 -> 6
    single_node *l2 = new single_node(2);
    l2->next = new single_node(4);
    l2->next->next = new single_node(6);

    // merge the two sorted linked lists
    single_node *merged = merge_sorted_lists(l1, l2);

    single_node *current = merged;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    // free the allocated memory
    current = merged;
    while (current != nullptr)
    {
        single_node *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}