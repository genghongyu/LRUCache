requirements:
    设计一个 LRU Cache，支持：

    get(key)：如果存在返回 value，否则返回 -1
    put(key, value)：
    如果 key 已存在，更新 value，并变为“最近使用”
    如果超过容量，删除“最久未使用”的 key

    要求：

    所有操作 O(1)