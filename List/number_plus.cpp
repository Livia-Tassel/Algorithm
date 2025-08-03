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

single_node *number_plus(single_node *l1, single_node *l2)
{
    single_node *ans = nullptr, *cur = nullptr;
    ll carry = 0;

    for (ll sum, val;
         // both the lists are null, then loop end
         l1 != nullptr || l2 != nullptr;
         l1 = (l1 ? l1->next : nullptr), l2 = (l2 ? l2->next : nullptr))
    {
        sum = (l1 ? l1->data : 0) + (l2 ? l2->data : 0) + carry;

        val = sum % 10;
        carry = sum / 10;

        // head node
        if (ans == nullptr)
        {
            ans = new single_node(val);
            cur = ans;
        }
        else
        {
            cur->next = new single_node(val);
            cur = cur->next;
        }
    }

    if (carry != 0)
    {
        cur->next = new single_node(1);
    }
    return ans;
}

signed main()
{
    // 1 -> 2 -> 3
    single_node *l1 = new single_node(1);
    l1->next = new single_node(2);
    l1->next->next = new single_node(3);

    // 4 -> 5 -> 6
    single_node *l2 = new single_node(4);
    l2->next = new single_node(5);
    l2->next->next = new single_node(6);

    // add the two linked lists
    single_node *result = number_plus(l1, l2);

    single_node *current = result;
    while (current != nullptr)
    {
        cout << current->data;
        current = current->next;
    }
    cout << endl;

    current = result;
    while (current != nullptr)
    {
        single_node *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}