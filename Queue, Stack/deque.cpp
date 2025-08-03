#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <cstdlib>
#define ll long long
using namespace std;

// std::list
// struct dequeue
// {
//     list<ll> l;
//     ll size, capacity;
//     dequeue(ll cap) : size(0), capacity(cap) {}

//     bool is_full()
//     {
//         return size == capacity;
//     }

//     void push_front(ll x)
//     {
//         if (!is_full())
//         {
//             l.push_front(x);
//             size++;
//         }
//         else
//         {
//             cout << "full\n";
//         }
//     }

//     void push_back(ll x)
//     {
//         if (!is_full())
//         {
//             l.push_back(x);
//             size++;
//         }
//         else
//         {
//             cout << "full\n";
//         }
//     }

//     void pop_front()
//     {
//         if (size > 0)
//         {
//             l.pop_front();
//             size--;
//         }
//         else
//         {
//             cout << "empty\n";
//         }
//     }

//     void pop_back()
//     {
//         if (size > 0)
//         {
//             l.pop_back();
//             size--;
//         }
//         else
//         {
//             cout << "empty\n";
//         }
//     }

//     void display()
//     {
//         for (auto it = l.begin(); it != l.end(); ++it)
//         {
//             cout << *it << " ";
//         }
//         cout << endl;
//     }

//     void clear()
//     {
//         l.clear();
//         size = 0;
//     }

//     void front()
//     {
//         if (size > 0)
//         {
//             cout << l.front() << endl;
//         }
//         else
//         {
//             cout << "empty\n";
//         }
//     }

//     void back()
//     {
//         if (size > 0)
//         {
//             cout << l.back() << endl;
//         }
//         else
//         {
//             cout << "empty\n";
//         }
//     }

//     void get_size()
//     {
//         cout << size << endl;
//     }

//     bool is_empty()
//     {
//         return size == 0;
//     }
// };

// arr
struct dequeue
{
    ll *arr;
    ll size, capacity, front, back;

    dequeue(ll cap) : size(0), capacity(cap), front(0), back(-1)
    {
        arr = new ll[capacity];
    }

    ~dequeue()
    {
        delete[] arr;
    }

    bool is_full()
    {
        return size == capacity;
    }

    void push_front(ll x)
    {
        if (!is_full())
        {
            // (x - 1 + capacity) % capacity ensures that front wraps around when it reaches the beginning
            front = (front - 1 + capacity) % capacity;
            arr[front] = x;
            size++;
        }
        else
        {
            cout << "full\n";
        }
    }

    void push_back(ll x)
    {
        if (!is_full())
        {
            // (x + 1) % capacity ensures that back wraps around when it reaches the end
            back = (back + 1) % capacity;
            arr[back] = x;
            size++;
        }
        else
        {
            cout << "full\n";
        }
    }

    void pop_front()
    {
        if (size > 0)
        {
            front = (front + 1) % capacity;
            size--;
        }
        else
        {
            cout << "empty\n";
        }
    }

    void pop_back()
    {
        if (size > 0)
        {
            back = (back - 1 + capacity) % capacity;
            size--;
        }
        else
        {
            cout << "empty\n";
        }
    }

    void display()
    {
        for (ll i = 0; i < size; i++)
        {
            cout << arr[(front + i) % capacity] << " ";
        }
        cout << endl;
    }

    void clear()
    {
        front = 0;
        back = -1;
        size = 0;
    }

    void front_value()
    {
        if (size > 0)
            cout << arr[front] << endl;
        else
            cout << "empty\n";
    }

    void back_value()
    {
        if (size > 0)
            cout << arr[back] << endl;
        else
            cout << "empty\n";
    }

    void get_size()
    {
        cout << size << endl;
    }

    bool is_empty()
    {
        return size == 0;
    }
};

signed main()
{
    dequeue dq(5);
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_back(4);
    dq.push_front(0);
    dq.push_front(-1);
    dq.display();
    dq.pop_back();
    dq.pop_front();
    dq.display();
    dq.get_size();
    dq.clear();
    dq.display();
}