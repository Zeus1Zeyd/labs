/**
 * @file UniqueSet.h
 * @brief Шаблонный класс для работы с множеством уникальных элементов
 */

#ifndef UNIQUESET_H
#define UNIQUESET_H

#include <iostream>

/**
 * @class UniqueSet
 * @brief Класс, реализующий функционал неупорядоченного множества уникальных элементов
 * @tparam T Тип элементов множества
 */
template<typename T>
class UniqueSet {
private:
    T* elements;        ///< Динамический массив элементов
    size_t capacity;    ///< Текущая вместимость массива
    size_t count;       ///< Количество элементов в множестве

    /**
     * @brief Увеличивает емкость массива при необходимости
     * @param newCapacity Новая емкость
     */
    void resize(size_t newCapacity);

    /**
     * @brief Проверяет, содержится ли элемент в множестве
     * @param element Элемент для проверки
     * @return true если элемент найден, иначе false
     */
    bool containsElement(const T& element) const;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    UniqueSet();

    /**
     * @brief Конструктор копирования
     * @param other Объект для копирования
     */
    UniqueSet(const UniqueSet& other);

    /**
     * @brief Деструктор, то есть освобождения ресурсов при уничтожении объекта
     */
    ~UniqueSet();

    /**
     * @brief Оператор присваивания
     * @param other Объект для копирования
     * @return Ссылка на текущий объект
     */
    UniqueSet& operator=(const UniqueSet& other);

    /**
     * @brief Добавляет элемент в множество
     * @param element Элемент для добавления
     */
    void add(const T& element);

    /**
     * @brief Проверяет наличие элемента в множестве
     * @param element Элемент для проверки
     * @return true если элемент найден, иначе false
     */
    bool contains(const T& element) const;

    /**
     * @brief Возвращает количество элементов в множестве
     * @return Количество элементов
     */
    size_t size() const;

    /**
     * @brief Проверяет, пусто ли множество
     * @return true если множество пусто, иначе false
     */
    bool isEmpty() const;

    /**
     * @brief Объединяет два множества
     * @param other Второе множество
     * @return Новое множество - объединение текущего и other
     */
    UniqueSet Union(const UniqueSet& other) const;

    /**
     * @brief Вычитает одно множество из другого
     * @param other Второе множество
     * @return Новое множество - разность текущего и other
     */
    UniqueSet Except(const UniqueSet& other) const;

    /**
     * @brief Находит пересечение двух множеств
     * @param other Второе множество
     * @return Новое множество - пересечение текущего и other
     */
    UniqueSet Intersect(const UniqueSet& other) const;

    /**
     * @brief Выводит элементы множества
     */
    void print() const;
};

#endif // UNIQUESET_H