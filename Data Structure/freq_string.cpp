#include <iostream>
#include <map>
#include <string>
#include <set>
#include <climits>
#define ll long long
using namespace std;

struct freq_string
{
    struct bucket
    {
        set<string> buk;
        ll freq;
        bucket *next, *last;

        bucket(ll f) : freq(f), next(nullptr), last(nullptr) {}
    };

    void after_bucket(bucket *cur, bucket *pos)
    {
        pos->next = cur->next;
        cur->next->last = pos;
        cur->next = pos;
        pos->last = cur;
    }

    void remove_bucket(bucket *cur)
    {
        cur->last->next = cur->next;
        cur->next->last = cur->last;
    }

    bucket *head, *tail;
    map<string, bucket *> mp;

    freq_string()
    {
        head = new bucket(0);
        tail = new bucket(LLONG_MAX);
        head->next = tail;
        tail->last = head;
    }

    ~freq_string()
    {
        bucket *cur = head;
        while (cur != nullptr)
        {
            bucket *next_buk = cur->next;
            delete cur;
            cur = next_buk;
        }
    }

    void inc(string k)
    {
        bucket *cur_buk;
        ll cur_freq;

        if (mp.find(k) == mp.end())
        {
            cur_buk = head;
            cur_freq = 0;
        }
        else
        {
            cur_buk = mp[k];
            cur_freq = cur_buk->freq;
            cur_buk->buk.erase(k);
        }

        ll next_freq = cur_freq + 1;
        if (cur_buk->next->freq != next_freq)
        {
            bucket *new_buk = new bucket(next_freq);
            after_bucket(cur_buk, new_buk);
        }

        bucket *next_buk = cur_buk->next;
        next_buk->buk.insert(k);
        mp[k] = next_buk;

        if (cur_buk != head && cur_buk->buk.empty())
        {
            remove_bucket(cur_buk);
            delete cur_buk;
        }
    }

    void dec(string k)
    {
        if (mp.find(k) == mp.end())
        {
            return;
        }

        bucket *cur_buk = mp[k];
        ll cur_freq = cur_buk->freq;

        cur_buk->buk.erase(k);

        if (cur_freq == 1)
        {
            mp.erase(k);
        }
        else
        {
            ll prev_freq = cur_freq - 1;
            if (cur_buk->last->freq != prev_freq)
            {
                bucket *new_buk = new bucket(prev_freq);
                after_bucket(cur_buk->last, new_buk);
            }
            bucket *prev_buk = cur_buk->last;
            prev_buk->buk.insert(k);
            mp[k] = prev_buk;
        }

        if (cur_buk->buk.empty())
        {
            remove_bucket(cur_buk);
            delete cur_buk;
        }
    }
};

void print_freq_state(const string &title, freq_string &fs)
{
    cout << "--- " << title << " ---" << endl;
    cout << "  list state (freq: {strings}): ";
    freq_string::bucket *cur = fs.head->next;
    while (cur != fs.tail)
    {
        cout << cur->freq << ":{";
        bool first = true;
        for (const auto &s : cur->buk)
        {
            if (!first)
                cout << ",";
            cout << s;
            first = false;
        }
        cout << "} ";
        cur = cur->next;
    }
    if (fs.head->next == fs.tail)
    {
        cout << "(empty)";
    }
    cout << endl;
    cout << "  map state: {";
    bool first = true;
    for (auto const &[key, b] : fs.mp)
    {
        if (!first)
            cout << ", ";
        cout << key << "->(freq:" << b->freq << ")";
        first = false;
    }
    cout << "}\n"
         << endl;
}

int main()
{
    freq_string fs;
    print_freq_state("initial state", fs);

    fs.inc("a");
    print_freq_state("inc(\"a\")", fs);
    fs.inc("b");
    print_freq_state("inc(\"b\")", fs);

    fs.inc("a");
    print_freq_state("inc(\"a\") again, creates freq=2 bucket", fs);

    fs.inc("b");
    print_freq_state("inc(\"b\") again, freq=1 bucket is removed", fs);

    fs.inc("c");
    print_freq_state("inc(\"c\")", fs);

    fs.dec("a");
    print_freq_state("dec(\"a\"), creates freq=1 bucket", fs);

    fs.dec("b");
    print_freq_state("dec(\"b\"), freq=2 bucket is removed", fs);

    fs.dec("a");
    print_freq_state("dec(\"a\") again, \"a\" is removed", fs);

    fs.dec("b");
    fs.dec("c");
    print_freq_state("dec(\"b\") and dec(\"c\"), all buckets removed", fs);

    fs.dec("z");
    print_freq_state("dec(\"z\"), state is unchanged", fs);

    return 0;
}