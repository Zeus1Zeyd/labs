/**
 * @file Dictionary.cpp
 * @brief Реализация методов класса Dictionary
 */

#include "Dictionary.h"
#include <stdexcept>
#include <algorithm>

template<typename K, typename V>
Dictionary<K, V>::Dictionary() : pairs(nullptr), capacity(0), count(0) {}

template<typename K, typename V>
Dictionary<K, V>::~Dictionary() {
    delete[] pairs;
}

template<typename K, typename V>
void Dictionary<K, V>::resize(size_t newCapacity) {
    using namespace std;
    KeyValuePair<K, V>* newPairs = new KeyValuePair<K, V>[newCapacity];
    for (size_t i = 0; i < count; i++) {
        newPairs[i] = pairs[i];
    }
    delete[] pairs;
    pairs = newPairs;
    capacity = newCapacity;
}

template<typename K, typename V>
int Dictionary<K, V>::findIndex(const K& key) const {
    using namespace std;
    for (size_t i = 0; i < count; i++) {
        if (pairs[i].key == key) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

template<typename K, typename V>
bool Dictionary<K, V>::add(const K& key, const V& value) {
    using namespace std;
    if (contains(key)) {
        return false;
    }
    
    if (count >= capacity) {
        resize(capacity == 0 ? 2 : capacity * 2);
    }
    
    pairs[count] = KeyValuePair<K, V>(key, value);
    count++;
    return true;
}

template<typename K, typename V>
bool Dictionary<K, V>::contains(const K& key) const {
    return findIndex(key) != -1;
}

template<typename K, typename V>
V Dictionary<K, V>::get(const K& key) const {
    using namespace std;
    int index = findIndex(key);
    if (index == -1) {
        throw runtime_error("Key not found");
    }
    return pairs[static_cast<size_t>(index)].value;
}

template<typename K, typename V>
void Dictionary<K, V>::set(const K& key, const V& value) {
    using namespace std;
    int index = findIndex(key);
    if (index != -1) {
        pairs[static_cast<size_t>(index)].value = value;
    } else {
        add(key, value);
    }
}

// Чтобы выполнялся именно этот класс
template class Dictionary<std::string, int>;