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
    bool containsKey(const K& key);
    V& get(const K& key);
    void put(const K& key, const V& value);
    int size();
    bool removeKey(const K& key);
    V& operator[](const K& key);
    BinaryTree<K> keySet();
};

//Clear method
template <typename K, typename V>
void TreeMap<K, V>::clear() {
    tree.clear();
}


//Returns true if this map contains a mapping for the specified key.
template <typename K, typename V>
bool TreeMap<K, V>::containsKey(const K& key) {
    try {
        KeyValue kv = { key, V() };
        tree.get(kv);
        return true;
    }
    catch (const std::logic_error&) {
        return false;
    }
}

//Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
template <typename K, typename V>
V& TreeMap<K, V>::get(const K& key) {
    KeyValue kv = { key, V() };
    return tree.get(kv).value;
}

//Associates the specified value with the specified key in this map
template <typename K, typename V>
void TreeMap<K, V>::put(const K& key, const V& value) {
    KeyValue kv = { key, value };

    if (containsKey(key)) {
        // If the key exists, update its value
        tree.get(kv).value = value;
    }
    else {
        //If not add a new KeyValue to the tree
        tree.add(kv);
    }
}


// Returns a Set view of the keys contained in this map.
template <typename K, typename V>
BinaryTree<K> TreeMap<K, V>::keySet() {
    BinaryTree<K> keys;
    KeyValue* allNodes = tree.toArray();
    for (int i = 0; i < tree.count(); i++) {
        keys.add(allNodes[i].key);
    }
    delete[] allNodes;
    return keys;
}

//Removes the item denoted by the given key.
template <typename K, typename V>
bool TreeMap<K, V>::removeKey(const K& key) {
    KeyValue kv = { key, V() };
    return tree.remove(kv);
}

//Returns the number of key-value mappings in this map
template <typename K, typename V>
int TreeMap<K, V>::size() {
    return tree.count();
}

//Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
template <typename K, typename V>
V& TreeMap<K, V>::operator[](const K& key) {
    if (!containsKey(key)) {
        throw std::logic_error("Key not found in TreeMap");
    }
    return get(key); 
}


