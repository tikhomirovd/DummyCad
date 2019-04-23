//
// Created by dimas on 4/12/19.
//

#ifndef CURVE_POINT_H
#define CURVE_POINT_H

#include "Curve_def.h"
#include <iostream>

using namespace std;

/**
 * \brief Класс, который задаёт точку \f$ M \f$.
 */
class Curve_EXPORT Point {
private:
    double _x = 0, _y = 0, _z = 0;


public:
    Point();

    explicit Point(double);

    Point(double, double);

    Point(double, double, double);

    /**
     * \brief Присваивает точке заданные координаты
     * @param x  координата \f$ M_x \f$
     * @param y  координата \f$ M_y \f$
     * @param z  координата \f$ M_z \f$
     */
    void setCoord(double x, double y, double z);

    /**
     * Возвращает координату \f$ x \f$ у точки
     * @return \f$ M_x \f$
     */
    double x();

    /**
     * Возвращает координату \f$ y \f$ у точки
     * @return \f$ M_y \f$
     */
    double y();

    /**
     * Возвращает координату \f$ x \f$ у точки
     * @return \f$ M_z \f$
     */
    double z();

    /**
     * Выводит на экран координаты точки
     */
    void getCoord();

    /**
     * Перегрузка оператора "+". Складывает точки покоординатно
     * @param a Точка \f$ A \f$
     * @param b Точка \f$ B \f$
     * @return  Точка \f$ \{A_x + B_x, A_y + B_y, A_z + B_z \} \f$
     */
    friend Point operator+(Point &a, Point &b) {

        return {a.x() + b.x(), a.y() + b.y(), a.z() + b.z()};
    }

    /**
     * Перегрузка оператора "*". Умножение вектора на число
     * @param a Точка \f$ A \f$
     * @param i Скаляр \f$ i \f$
     * @return  Точка \f$ \{A_x * i, A_y * i, A_z * i \} \f$
     */
    friend const Point operator*(Point &a, const double &i) {

        return {a.x() * i, a.y() * i, a.z() * i};
    }

    /**
     * Перегрузка оператора "+". Прибавление к вектору число покоординатно
     * @param a Точка \f$ A \f$
     * @param i Скаляр  \f$ i \f$
     * @return  Точка \f$ \{A_x + i, A_y + i, A_z + i\} \f$
     */
    friend const Point operator+(Point &a, const double &i) {

        return {a.x() + i, a.y() + i, a.z() + i};
    }


};


#endif //CURVE_POINT_H
