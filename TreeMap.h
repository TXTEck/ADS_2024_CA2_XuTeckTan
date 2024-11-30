#pragma once
using namespace std;
#include "BinaryTree.h"

template <typename K, typename V>
class TreeMap {
private:
    struct KeyValue {
        K key;
        V value;

        bool operator<(const KeyValue& other) const { return key < other.key; }
        bool operator>(const KeyValue& other) const { return key > other.key; }
        bool operator==(const KeyValue& other) const { return key == other.key; }
    };

    BinaryTree<KeyValue> tree;

public:
    TreeMap() = default;
    void clear();
    bool containsKey(const K& key) const;
    V& get(const K& key);
    void put(const K& key, const V& value);
    int size() const;
    bool removeKey(const K& key);
    V& operator[](const K& key);

    BinaryTree<K> keySet() const;
};

//Clear method
template <typename K, typename V>
void TreeMap<K, V>::clear() {
	tree.clear();
}


//Returns true if this map contains a mapping for the specified key.
template <typename K, typename V>
bool TreeMap<K, V>::containsKey(const K& key) const {
    try {
        KeyValue kv = { key, V() };
        tree.get(kv);
        return true;
    }
    catch (const std::logic_error&) {
        return false;
    }
}

