#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <cstdlib>
#define ll long long
using namespace std;

struct circular_queue
{
    vector<ll> data;
    ll front;
    ll rear;
    ll capacity;

    circular_queue(ll size)
    {
        data.resize(size);
        front = 0;
        rear = 0;
        capacity = size;
    }

    // the circular queue can only store capacity - 1 elements to distinguish full and empty states
    bool is_full()
    {
        return (rear + 1) % capacity == front;
    }

    bool is_empty()
    {
        return front == rear;
    }

    void enqueue(ll value)
    {
        if (is_full())
        {
            cout << "full\n";
            return;
        }
        data[rear] = value;
        rear = (rear + 1) % capacity;
    }

    ll dequeue()
    {
        if (is_empty())
        {
            cout << "empty\n";
            return -1;
        }
        ll value = data[front];
        front = (front + 1) % capacity;
        return value;
    }

    ll peek()
    {
        if (is_empty())
        {
            cout << "empty\n";
            return -1;
        }
        return data[front];
    }
};

struct stack_sim_queue
{
    stack<ll> stack_in, stack_out;

    void enqueue(ll value)
    {
        stack_in.push(value);
    }

    // transfer elements from stack_in to stack_out
    void IntoOut()
    {
        // only if the stack_out is empty, can we transfer elements from stack_in to stack_out
        if (stack_out.empty())
        {
            // if we transfer elements from stack_in to stack_out, the stack_in must become empty
            while (!stack_in.empty())
            {
                stack_out.push(stack_in.top());
                stack_in.pop();
            }
        }
    }

    ll dequeue()
    {
        IntoOut();
        if (stack_out.empty())
        {
            cout << "empty\n";
            return -1;
        }
        ll value = stack_out.top();
        stack_out.pop();
        return value;
    }

    ll peek()
    {
        IntoOut();
        if (stack_out.empty())
        {
            cout << "empty\n";
            return -1;
        }
        return stack_out.top();
    }

    bool is_empty()
    {
        return stack_in.empty() && stack_out.empty();
    }
};

struct queue_sim_stack
{
    queue<ll> q;

    void push(ll value)
    {
        ll size = q.size();
        q.push(value);
        // rotate the queue to the front
        for (ll i = 0; i < size - 1; ++i)
        {
            q.push(q.front());
            q.pop();
        }
    }

    ll pop()
    {
        if (q.empty())
        {
            cout << "empty\n";
            return -1;
        }
        ll value = q.front();
        q.pop();
        return value;
    }

    ll top()
    {
        if (q.empty())
        {
            cout << "empty\n";
            return -1;
        }
        return q.front();
    }

    ll empty()
    {
        return q.empty();
    }
};

signed main()
{
    circular_queue cq(5);
    cq.enqueue(1);
    cq.enqueue(2);
    cq.enqueue(3);
    cout << "Dequeue: " << cq.dequeue() << endl; // 1
    cout << "Peek: " << cq.peek() << endl;       // 2
    cq.enqueue(4);
    cq.enqueue(5);
    cq.enqueue(6);
    cout << "Dequeue: " << cq.dequeue() << endl; // 2

    stack_sim_queue ssq;
    ssq.enqueue(10);
    ssq.enqueue(20);
    cout << "Dequeue: " << ssq.dequeue() << endl; // 10
    cout << "Peek: " << ssq.peek() << endl;       // 20

    queue_sim_stack qss;
    qss.push(100);
    qss.push(200);
    cout << "Pop: " << qss.pop() << endl; // 200
    cout << "Top: " << qss.top() << endl; // 100

    return 0;
}