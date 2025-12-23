/**
 * @file Point3D.h
 * @brief Классы для работы с двухмерными и трехмерными точками
 */

#ifndef POINT3D_H
#define POINT3D_H

#include <string>
#include <cmath>

/**
 * @class Point2D
 * @brief Класс для работы с двухмерной точкой
 */
class Point2D {
private:
    double x; ///< Координата X
    double y; ///< Координата Y

public:
    /**
     * @brief Конструктор с параметрами
     * @param xCoord Координата X
     * @param yCoord Координата Y
     */
    Point2D(double xCoord, double yCoord);
    
    /**
     * @brief Конструктор по умолчанию
     */
    Point2D();
    
    /**
     * @brief Получает координату X
     * @return Координата X
     */
    double getX() const;
    
    /**
     * @brief Получает координату Y
     * @return Координата Y
     */
    double getY() const;
    
    /**
     * @brief Преобразует точку в строку
     * @return Строковое представление точки
     */
    virtual std::string toString() const;
    
    /**
     * @brief Выводит информацию о точке
     */
    void print() const;
    
    /**
     * @brief Вычисляет расстояние до другой точки
     * @param other Другая точка
     * @return Расстояние между точками
     */
    virtual double distanceTo(const Point2D& other) const;
    
    /**
     * @brief Виртуальный деструктор для наследования
     */
    virtual ~Point2D() = default;
};

/**
 * @class Point3D
 * @brief Класс для работы с трехмерной точкой, наследуется от Point2D
 */
class Point3D : public Point2D {
private:
    double z; ///< Координата Z

public:
    /**
     * @brief Конструктор с параметрами
     * @param xCoord Координата X
     * @param yCoord Координата Y
     * @param zCoord Координата Z
     */
    Point3D(double xCoord, double yCoord, double zCoord);
    
    /**
     * @brief Конструктор по умолчанию
     */
    Point3D();
    
    /**
     * @brief Преобразует точку в строку (переопределение)
     * @return Строковое представление точки
     */
    std::string toString() const override;
    
    /**
     * @brief Вычисляет расстояние до другой трехмерной точки
     * @param other Другая трехмерная точка
     * @return Расстояние между точками
     */
    double distanceTo(const Point3D& other) const;
    
    /**
     * @brief Вычисляет расстояние до другой точки (переопределение)
     * @param other Другая точка
     * @return Расстояние между точками
     */
    // double distanceTo(const Point2D& other) const override;
};

#endif // POINT3D_H