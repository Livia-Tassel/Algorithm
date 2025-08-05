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

node *goto_k(node *s, ll k)
{
    if (s == nullptr)
        return nullptr;
    node *temp = s;
    for (ll i = 0; i < k - 1 && temp != nullptr; i++)
    {
        temp = temp->next;
    }
    return temp;
}

void reverse(node *start, node *end)
{
    end = end->next;
    node *prev = nullptr, *current = start, *next = nullptr;
    while (current != end)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    start->next = end;
}

// reverse a linked list in groups of k, and leave the last group as-is if it has fewer than k elements.
node *k_reverse(node *head, ll k)
{
    node *start = head, *end = goto_k(head, k);
    if (end == nullptr)
        return head;

    head = end;
    reverse(start, end);
    node *last_team_end = start;
    while (last_team_end->next != nullptr)
    {
        start = last_team_end->next;
        end = goto_k(start, k);
        if (end == nullptr)
            return head;
        reverse(start, end);
        last_team_end->next = end;
        last_team_end = start;
    }

    return head;
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

signed main()
{
    node *head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = new node(5);

    ll k = 2;
    head = k_reverse(head, k);

    node *temp = head;
    while (temp != nullptr)
    {
        printf("%lld ", temp->data);
        temp = temp->next;
    }

    delete_linked_list(head);
    printf("\n");

    return 0;
}
