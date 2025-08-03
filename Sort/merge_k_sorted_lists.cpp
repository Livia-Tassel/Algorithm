#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define ll long long
using namespace std;

struct node
{
    ll val;
    node *next;

    node(ll x) : val(x), next(nullptr) {}
};

struct CompareNodePointers
{
    bool operator()(const node *a, const node *b) const
    {
        return a->val > b->val; // min_heap
    }
};

node *merge_k_sorted_lists(vector<node *> &lists)
{
    priority_queue<node *, vector<node *>, CompareNodePointers> min_heap;

    for (node *list_head : lists)
    {
        if (list_head)
        {
            min_heap.push(list_head);
        }
    }

    if (min_heap.empty())
    {
        return nullptr;
    }

    node *min_node = min_heap.top();
    min_heap.pop();

    node *head = min_node;

    if (min_node->next)
    {
        min_heap.push(min_node->next);
    }

    node *current = head;
    while (!min_heap.empty())
    {
        min_node = min_heap.top();
        min_heap.pop();

        current->next = min_node;
        current = current->next;

        if (min_node->next)
        {
            min_heap.push(min_node->next);
        }
    }

    return head;
}

void delete_list(node *head)
{
    while (head)
    {
        node *temp = head;
        head = head->next;
        delete temp;
    }
}

signed main()
{
    vector<node *> lists;

    // 1: 1 -> 2 -> null
    node *list_1 = new node(1);
    list_1->next = new node(2);
    lists.push_back(list_1);

    // 2: 4 -> 5 -> null
    node *list_2 = new node(4);
    list_2->next = new node(5);
    lists.push_back(list_2);

    // 3: 3 -> 6 -> null
    node *list_3 = new node(3);
    list_3->next = new node(6);
    lists.push_back(list_3);

    node *merged_head = merge_k_sorted_lists(lists);
    node *current = merged_head;
    while (current)
    {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;

    delete_list(merged_head);
    return 0;
}