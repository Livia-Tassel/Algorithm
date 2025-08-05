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

// return the first intersecting node of two linked lists.
//      \     /
//       \   /
//        \ /
//         X
//         |
//         |
node *list_intersecting(node *ho, node *ht)
{
    if (ho == nullptr || ht == nullptr)
        return nullptr;

    node *po = ho;
    node *pt = ht;

    // length of both lists
    ll lo = 1, lt = 1;
    while (po->next != nullptr)
    {
        lo++;
        po = po->next;
    }
    while (pt->next != nullptr)
    {
        lt++;
        pt = pt->next;
    }

    if (po != pt)
    {
        return nullptr;
    }

    // reset pointers
    po = ho;
    pt = ht;

    // align the start of both lists
    if (lo > lt)
    {
        for (ll i = 0; i < lo - lt; i++)
            po = po->next;
    }
    else
    {
        for (ll i = 0; i < lt - lo; i++)
            pt = pt->next;
    }

    // go together
    while (po != pt)
    {
        po = po->next;
        pt = pt->next;
    }

    return po;
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
    node *ho = new node(1);
    ho->next = new node(2);
    ho->next->next = new node(3);
    ho->next->next->next = new node(4);

    node *ht = new node(5);
    ht->next = new node(6);
    ht->next->next = ho->next->next; // node 3

    node *both = list_intersecting(ho, ht);
    if (both)
        cout << "Intersecting at Node with Value: " << both->data << endl;
    else
        cout << "No Intersection Found." << endl;

    if (both != nullptr)
    {
        ht->next->next = nullptr;
    }

    delete_linked_list(ho);
    delete_linked_list(ht);

    return 0;
}
