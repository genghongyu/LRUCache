#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CLRUCache {
public:
    explicit CLRUCache(int size):m_size(size) {
        m_container.reserve(m_size);
    }

    // rule of five 先不考虑

    // 获取key对应的value，如果不存在，返回-1
    int get(int key) const {
        for (const auto& item : m_container) {
            if (item.first == key) {
                return item.second;
            }
        }
        return -1;
    }

    // 如果存在，更新。
    // 不存在，push_back
    // 超过容量，删除最旧（vector front）
    void put(int key, int val) {
        for (int i = 0; i < m_container.size(); i++) {
            if (m_container[i].first == key) {
                // 找到，更新val，立即返回
                m_container[i].second = val;
                return;
            }
        }

        // 判断是否满了
        if (m_container.size() == m_size) {
            m_container.erase(m_container.begin());
        }

        // 追加元素
        m_container.push_back({key, val});
    }

private:
    int m_size = 0;
    vector<pair<int, int>> m_container;
};




int main()
{
    CLRUCache cache(5);

    // 追加元素
    cache.put(1, 34);
    cache.put(2, 56);
    cache.put(5, 57);
    cache.put(6, 193);
    cache.put(3, 23);
    
    // 打印元素
    cout << cache.get(1) << endl;
    cout << cache.get(10) << endl;
    




    return 0;
}