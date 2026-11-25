#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2627_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key)
    {
        unsigned long long suma = 0;

        for (unsigned char c : key)
        {
            suma += c;
        }

        return suma % max;
    }

public:
    HashTable(int size)
        : n(0), max(size), table(nullptr)
    {
        if (size <= 0)
        {
            throw std::invalid_argument("Invalid table size");
        }

        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() override
    {
        delete[] table;
    }

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    int capacity()
    {
        return max;
    }

    int entries() override
    {
        return n;
    }

    void insert(std::string key, V value) override
    {
        int pos = h(key);

        TableEntry<V> entry(key, value);

        if (table[pos].search(entry) != -1)
        {
            throw std::runtime_error("Key already exists");
        }

        table[pos].append(entry);

        n++;
    }

    V search(std::string key) override
    {
        int pos = h(key);

        TableEntry<V> entry(key);

        int ind = table[pos].search(entry);

        if (ind == -1)
        {
            throw std::runtime_error("Key not found");
        }

        return table[pos].get(ind).value;
    }

    V remove(std::string key) override
    {
        int pos = h(key);

        TableEntry<V> entry(key);

        int ind = table[pos].search(entry);

        if (ind == -1)
        {
            throw std::runtime_error("Key not found");
        }

        TableEntry<V> removed = table[pos].remove(ind);

        n--;

        return removed.value;
    }

    V operator[](std::string key)
    {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const HashTable<V>& th)
    {
        out << "Entries: " << th.n << '\n';
        out << "Capacity: " << th.max << '\n';

        for (int i = 0; i < th.max; i++)
        {
            out << i << ": " << th.table[i];
        }

        return out;
    }
};

#endif
