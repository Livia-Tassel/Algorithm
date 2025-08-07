#include <iostream>
#include <map>
#define ll long long
using namespace std;

// Least Recently Used
struct cache
{
    struct double_node
    {
        ll key, val;
        double_node *last, *next;
        double_node(ll k, ll v) : key(k), val(v), last(nullptr), next(nullptr) {}
    };

    struct double_list
    {
        double_node *head, *tail;
        double_list() : head(nullptr), tail(nullptr) {}

        void add_to_tail(double_node *node)
        {
            if (node == nullptr)
                return;
            if (head == nullptr)
            {
                head = node;
                tail = node;
            }
            else
            {
                tail->next = node;
                node->last = tail;
                node->next = nullptr;
                tail = node;
            }
        }

        void move_to_tail(double_node *node)
        {
            if (tail == node)
                return;
            if (head == node)
            {
                head = head->next;
                if (head)
                    head->last = nullptr;
            }
            else
            {
                node->last->next = node->next;
                if (node->next)
                    node->next->last = node->last;
            }
            add_to_tail(node);
        }

        double_node *remove_head()
        {
            if (head == nullptr)
                return nullptr;
            double_node *ans = head;
            if (head == tail)
            {
                head = nullptr;
                tail = nullptr;
            }
            else
            {
                head = ans->next;
                if (head)
                    head->last = nullptr;
                ans->next = nullptr;
            }
            return ans;
        }
    };

    ll capacity;
    map<ll, double_node *> key_to_node;
    double_list list;

    cache(ll cap) : capacity(cap) {}

    ~cache()
    {
        double_node *current = list.head;
        while (current != nullptr)
        {
            double_node *next = current->next;
            delete current;
            current = next;
        }
    }

    ll get_value(ll k)
    {
        if (key_to_node.count(k))
        {
            double_node *pos = key_to_node[k];
            list.move_to_tail(pos);
            return pos->val;
        }
        return -1;
    }

    void insert(ll k, ll v)
    {
        if (key_to_node.count(k))
        {
            double_node *pos = key_to_node[k];
            pos->val = v;
            list.move_to_tail(pos);
        }
        else
        {
            if (key_to_node.size() == capacity)
            {
                double_node *lru_node = list.remove_head();
                key_to_node.erase(lru_node->key);
                delete lru_node;
            }
            double_node *new_node = new double_node(k, v);
            key_to_node[k] = new_node;
            list.add_to_tail(new_node);
        }
    }
};

void print_cache_state(cache &lru_cache)
{
    cout << "  Cache State (LRU -> MRU): [";
    cache::double_node *current = lru_cache.list.head;
    bool first = true;
    while (current != nullptr)
    {
        if (!first)
        {
            cout << ", ";
        }
        cout << "(" << current->key << ":" << current->val << ")";
        first = false;
        current = current->next;
    }
    cout << "]" << endl;
}

signed main()
{
    cache lru_cache(3);
    cout << "created a cache with capacity 3." << endl;

    cout << "\n--- test 1: basic insertion ---" << endl;
    lru_cache.insert(1, 10);
    cout << "Inserted (1, 10)." << endl;
    print_cache_state(lru_cache);

    lru_cache.insert(2, 20);
    cout << "Inserted (2, 20)." << endl;
    print_cache_state(lru_cache);

    lru_cache.insert(3, 30);
    cout << "Inserted (3, 30). cache is now full." << endl;
    print_cache_state(lru_cache);

    cout << "\n--- test 2: 'get' operation and reordering ---" << endl;
    cout << "accessing key 1... value: " << lru_cache.get_value(1) << endl;
    cout << "key 1 should now be the most recently used." << endl;
    print_cache_state(lru_cache);

    cout << "\n--- test 3: eviction ---" << endl;
    lru_cache.insert(4, 40);
    cout << "Inserted (4, 40). key 2 (the LRU) should be evicted." << endl;
    print_cache_state(lru_cache);

    cout << "\n--- test 4: updating an existing key ---" << endl;
    lru_cache.insert(3, 333);
    cout << "updated (3, 333). value should change and it should become MRU." << endl;
    print_cache_state(lru_cache);

    cout << "\n--- test 5: edge cases ---" << endl;
    cout << "getting a non-existent key 99... value: " << lru_cache.get_value(99) << endl;
    cout << "cache state should be unchanged." << endl;
    print_cache_state(lru_cache);

    return 0;
}