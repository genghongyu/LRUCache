#include <iostream>
#include <string>
#include <iterator>
#include <list>
#include <unordered_map>

using namespace std;

class CLRUCache {
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

        // Get value through iterator
        auto value = (iter->second)->second;

        // Remove the element from the list
        m_list.erase(iter->second);

        // Add the element to the tail
        m_list.push_back({key, value});

        // Update iterator stored in the map
        auto new_iter = prev(m_list.end());
        iter->second = new_iter;

        return value;
    }

    /*
        If the key already exists, update it.
        If the key does not exist and capacity is not full, append it.
        If the key does not exist and capacity is full,
        remove the oldest element and append the new one.
    */
    void put(int key, int val) {
        if (m_map.count(key)) {
            // Remove the existing element from the list
            m_list.erase(m_map[key]);

            // Add updated element to the tail
            m_list.push_back({key, val});

            // Update iterator stored in the map
            auto new_iter = prev(m_list.end());
            m_map[key] = new_iter;
            return;
        }

        if (m_map.size() != m_size) {
            // Cache is not full, append new element
            m_list.push_back({key, val});
            auto iter = prev(m_list.end());
            m_map[key] = iter;

            return;
        } else {
            // Cache is full

            // Remove the oldest element from the list
            auto item = m_list.front();
            m_list.pop_front();

            // Remove the corresponding key from the map
            m_map.erase(item.first);

            // Append the new element
            m_list.push_back({key, val});
            auto iter = prev(m_list.end());
            m_map[key] = iter;

            return;
        }
    }

    /*
        Display cache information
    */
   void showinfo() const {
        cout << "---------------------------" << endl;

        for(const auto& item : m_list) {
            cout << "key=" << item.first
                 << " val=" << item.second << endl;
        }

        cout << "---------------------------" << endl;
   }

private:
    int m_size = 0;

    // Store cache data in LRU order
    list<pair<int, int>> m_list;

    // key -> iterator in list
    unordered_map<int, list<pair<int, int>>::iterator> m_map;
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