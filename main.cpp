#include <iostream>
#include <string>
#include <iterator>
#include <list>
#include <unordered_map>

using namespace std;

using ListIter = list<pair<int, int>>::iterator;
class CLRUCache {
private:
    void add_to_tail(int key, int val) {
        m_list.emplace_back(key, val);

        // the iterator of the last element in list
        auto iter = prev(m_list.end());

        // add data into map
        m_map[key] = iter;
    }

public:
    explicit CLRUCache(int size):m_size(size) {
        m_map.reserve(m_size);
    }

    /*
        Search key in the map.
        (1) If found:
            Return the corresponding value and move the element
            to the end of the list (most recently used).
        (2) If not found:
            Return -1.
    */
    int get(int key) {
        auto iter = m_map.find(key);
        if (iter == m_map.end()) {
            return -1;
        }

        // move the found item to the tail of the list
        m_list.splice(m_list.end(), m_list, iter->second);

        return iter->second->second;
    }

    /*
        If the key already exists, update it.
        If the key does not exist and capacity is not full, append it.
        If the key does not exist and capacity is full,
        remove the oldest element and append the new one.
    */
    void put(int key, int val) {
        auto iter = m_map.find(key);
        if (iter != m_map.end()) {
            // find the key int the map, update the value
            iter->second->second = val;

            // update the pos in the list
            m_list.splice(m_list.end(), m_list, iter->second);
            return;
        }

        if (m_map.size() < m_size) {
            // Cache is not full, append new element to the list and map
            add_to_tail(key, val);
            return;
        } else {
            // Cache is full
            // Remove the corresponding key from the map
            m_map.erase(m_list.front().first);

            // Remove the oldest element from the list
            m_list.pop_front();

            // Append the new element
            add_to_tail(key, val);

            return;
        }
    }

    /*
        Display cache information
    */
   void showinfo() const {
        for(const auto& item : m_list) {
            cout << "key=" << item.first
                 << " val=" << item.second << endl;
        }
   }

private:
    size_t m_size = 0;

    // Store cache data in LRU order
    list<pair<int, int>> m_list;

    // key -> iterator in list
    unordered_map<int, ListIter> m_map;
};


int main()
{
    CLRUCache cache(5);

    // Insert elements
    cache.put(1, 23);
    cache.put(5, 12);
    cache.put(12, 6);

    // Get existing element
    cout << cache.get(5) << endl;

    // Get non-existing element
    cout << cache.get(51) << endl;

    // Insert more elements
    cache.put(4, 67);
    cache.put(45, 2);

    cache.showinfo();

    // Access element
    cout << cache.get(4) << endl;

    cache.showinfo();

    return 0;
}