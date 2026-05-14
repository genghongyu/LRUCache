#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CLRUCache {
public:
    explicit CLRUCache(int size):m_size(size) {
        m_container.reserve(m_size);
    }


    /*
        获取key对应的value。
        没找到，返回-1.
        找到，返回value，并将元素移动到vector尾部，表示最新使用
    */
    int get(int key) {
        for (int i = 0; i < m_container.size(); i++) {
            if (m_container[i].first == key) {
                // 找到key
                auto tmp_item = m_container[i];

                // 删除元素
                m_container.erase(m_container.begin() + i);

                // 尾部追加元素
                m_container.push_back(tmp_item);

                return tmp_item.second;
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

    ///////////////////////////////////////////////
    void showinfo() const {
        cout << "size=" << m_container.size() << " capacity=" << m_container.capacity() << endl;
        for (const auto& item : m_container) {
            cout << "key=" << item.first << " value=" << item.second << endl;
        }
    }

private:
    int m_size = 0;
    vector<pair<int, int>> m_container;
};


int main()
{
    CLRUCache cache(5);

    // 追加元素
    cache.put(1, 23);
    cache.put(5, 12);
    cache.put(12, 6);
    cache.showinfo();

    // 获取元素
    cout << cache.get(5) << endl;
    cache.showinfo();



    return 0;
}