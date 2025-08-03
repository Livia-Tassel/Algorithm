#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#define ll long long
using namespace std;

struct single_node
{
    ll data;
    single_node *next;
    single_node(ll val) : data(val), next(nullptr) {}
};

// divide the list into two parts, the number of one less than x and the other part is greater than or equal to x, keeping the relative order of the nodes in each part.
single_node *partition(single_node *head, ll x)
{
    single_node *less_head = nullptr, *less_tail = nullptr;
    single_node *greater_head = nullptr, *greater_tail = nullptr;
    single_node *next = nullptr;
    while (head != nullptr)
    {
        next = head->next;    // store the next node
        head->next = nullptr; // break the link to avoid cycles
        if (head->data < x)
        {
            if (less_head == nullptr)
            {
                less_head = head;
                less_tail = head;
            }
            else
            {
                less_tail->next = head;
                less_tail = less_tail->next;
            }
        }
        else
        {
            if (greater_head == nullptr)
            {
                greater_head = head;
                greater_tail = head;
            }
            else
            {
                greater_tail->next = head;
                greater_tail = greater_tail->next;
            }
        }
        head = next; // move to the next node
    }
    // there is no element less than x
    if (less_tail == nullptr)
    {
        return greater_head;
    }
    less_tail->next = greater_head; // connect the two parts
    return less_head;
}
signed main()
{
    // 6 -> 5 -> 3 -> 4 -> 2 -> 1 -> 1 -> 7
    single_node *head = new single_node(6);
    head->next = new single_node(5);
    head->next->next = new single_node(3);
    head->next->next->next = new single_node(4);
    head->next->next->next->next = new single_node(2);
    head->next->next->next->next->next = new single_node(1);
    head->next->next->next->next->next->next = new single_node(1);
    head->next->next->next->next->next->next->next = new single_node(7);
    single_node *ans = partition(head, 3);
    while (ans != nullptr)
    {
        cout << ans->data << " ";
        ans = ans->next;
    }
    return 0;
}