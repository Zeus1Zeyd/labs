/**
 * @file Dictionary.h
 * @brief Шаблонный класс для работы со словарем
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>

/**
 * @brief Структура для хранения пары ключ-значение
 * @tparam K Тип ключа
 * @tparam V Тип значения
 */
template<typename K, typename V>
struct KeyValuePair {
    K key;      ///< Ключ
    V value;    ///< Значение
    
    /**
     * @brief Конструктор по умолчанию
     */
    KeyValuePair() : key(), value() {}
    
    /**
     * @brief Конструктор с параметрами
     * @param k Ключ
     * @param v Значение
     */
    KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
    
    /**
     * @brief Конструктор копирования
     * @param other Объект для копирования
     */
    KeyValuePair(const KeyValuePair& other) : key(other.key), value(other.value) {}
    
    /**
     * @brief Оператор присваивания
     * @param other Объект для копирования
     * @return Ссылка на текущий объект
     */
    KeyValuePair& operator=(const KeyValuePair& other) {
        if (this != &other) {
            key = other.key;
            value = other.value;
        }
        return *this;
    }
};

/**
 * @class Dictionary
 * @brief Класс, реализующий функционал словаря с уникальными ключами
 * @tparam K Тип ключа
 * @tparam V Тип значения
 */
template<typename K, typename V>
class Dictionary {
private:
    KeyValuePair<K, V>* pairs;   ///< Массив пар ключ-значение
    size_t capacity;              ///< Текущая вместимость
    size_t count;                 ///< Количество элементов
    
    /**
     * @brief Увеличивает емкость массива
     * @param newCapacity Новая емкость
     */
    void resize(size_t newCapacity);
    
    /**
     * @brief Находит индекс элемента по ключу
     * @param key Ключ для поиска
     * @return Индекс элемента или -1 если не найден
     */
    int findIndex(const K& key) const;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Dictionary();
    
    /**
     * @brief Деструктор
     */
    ~Dictionary();
    
    /**
     * @brief Добавляет элемент в словарь
     * @param key Ключ
     * @param value Значение
     * @return true если успешно добавлено, false если ключ уже существует
     */
    bool add(const K& key, const V& value);
    
    /**
     * @brief Проверяет наличие ключа в словаре
     * @param key Ключ для проверки
     * @return true если ключ существует, иначе false
     */
    bool contains(const K& key) const;
    
    /**
     * @brief Получает значение по ключу
     * @param key Ключ
     * @return Значение по ключу
     * @throws std::runtime_error если ключ не найден
     */
    V get(const K& key) const;
    
    /**
     * @brief Устанавливает значение по ключу (добавляет или обновляет)
     * @param key Ключ
     * @param value Значение
     */
    void set(const K& key, const V& value);
    
};

#endif // DICTIONARY_H