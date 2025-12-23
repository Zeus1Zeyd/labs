/**
 * @file UniqueSet.cpp
 * @brief Реализация методов класса UniqueSet
 */

#include "UniqueSet.h"
#include <algorithm>
#include <stdexcept>


template<typename T>
UniqueSet<T>::UniqueSet() : elements(nullptr), capacity(0), count(0) {}

template<typename T>
UniqueSet<T>::UniqueSet(const UniqueSet& other) : capacity(other.capacity), count(other.count) {
    using namespace std;
    if (capacity > 0) {
        elements = new T[capacity]; // Выделяем динамическую память под массив из capacity элементов типа T
        for (size_t i = 0; i < count; i++) { // Cохраняем указатель на этот массив в поле elements
            elements[i] = other.elements[i];
        }
    } else {
        elements = nullptr;
    }
}

template<typename T>
UniqueSet<T>::~UniqueSet() {
    using namespace std;
    delete[] elements;
}

template<typename T>
UniqueSet<T>& UniqueSet<T>::operator=(const UniqueSet& other) {
    using namespace std;
    if (this != &other) {
        delete[] elements;
        capacity = other.capacity;
        count = other.count;
        if (capacity > 0) {
            elements = new T[capacity];
            for (size_t i = 0; i < count; i++) {
                elements[i] = other.elements[i];
            }
        } else {
            elements = nullptr;
        }
    }
    return *this;
}

template<typename T>
void UniqueSet<T>::resize(size_t newCapacity) {
    using namespace std;
    T* newElements = new T[newCapacity];
    for (size_t i = 0; i < count; i++) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

template<typename T>
bool UniqueSet<T>::containsElement(const T& element) const {
    using namespace std;
    for (size_t i = 0; i < count; i++) {
        if (elements[i] == element) {
            return true;
        }
    }
    return false;
}

template<typename T>
void UniqueSet<T>::add(const T& element) {
    using namespace std;
    if (!containsElement(element)) {
        if (count >= capacity) {
            resize(capacity == 0 ? 2 : capacity * 2);
        }
        elements[count++] = element;
    }
}

template<typename T>
bool UniqueSet<T>::contains(const T& element) const {
    return containsElement(element);
}

template<typename T>
size_t UniqueSet<T>::size() const {
    return count;
}

template<typename T>
bool UniqueSet<T>::isEmpty() const {
    return count == 0;
}

template<typename T>
UniqueSet<T> UniqueSet<T>::Union(const UniqueSet& other) const {
    using namespace std;
    UniqueSet result(*this);
    for (size_t i = 0; i < other.count; i++) {
        result.add(other.elements[i]);
    }
    return result;
}

template<typename T>
UniqueSet<T> UniqueSet<T>::Except(const UniqueSet& other) const {
    using namespace std;
    UniqueSet result;
    for (size_t i = 0; i < count; i++) {
        if (!other.containsElement(elements[i])) {
            result.add(elements[i]);
        }
    }
    return result;
}

template<typename T>
UniqueSet<T> UniqueSet<T>::Intersect(const UniqueSet& other) const {
    using namespace std;
    UniqueSet result;
    for (size_t i = 0; i < count; i++) {
        if (other.containsElement(elements[i])) {
            result.add(elements[i]);
        }
    }
    return result;
}

template<typename T>
void UniqueSet<T>::print() const {
    using namespace std;
    cout << "{ ";
    for (size_t i = 0; i < count; i++) {
        cout << elements[i];
        if (i < count - 1) cout << ", ";
    }
    cout << " }" << endl;
}

// Для того чтобы использовался именно этот класс
template class UniqueSet<std::string>;
template class UniqueSet<int>;