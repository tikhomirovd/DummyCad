//
// Created by dimas on 4/18/19.
//

#ifndef CURVE_INTERSECTION_H
#define CURVE_INTERSECTION_H

#include <Curve.h>
#include <Line.h>
#include <iostream>
#include <Circle.h>
#include <memory>
#include <Point.h>
#include <vector>

using namespace std;


/**
* \brief Вычисляет определитель матрицы 2х2
* \return Определитель
*/
static double det(double, double, double, double);

/**
 * \brief   Класс, который вычисляет точки, в которых кривые пересекаются
 */
class Curve_EXPORT Intersection
{
public:
    enum InterStatus
    {
        DONE,
        NOT_INTERSECTED,
        EQUAL
    };

private:
    vector<Point> inter = {};
    InterStatus status;


public:
    
    /**
     * \brief Начальная инициализация класса по двум кривым. Кривые могут быть или кругом, или прямой.
     * \param curve1 - Первая кривая
     * \param curve2 - Вторая кривая
     */
    Intersection(const shared_ptr<Curve> &, const shared_ptr<Curve> &);
    
    
    /**
    * \brief Проверяет, являются ли прямые параллельными
    * \param line1 Первая линия
    * \param line2 Вторая линия
     *
    */
    static bool IsParallel(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2);
    
    
    /**
    * \brief Проверяет, совпадают ли прямые
    * \param line1 Первая линия
    * \param line2 Вторая линия
     *
    */
    static bool IsEquivalent(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2);
    
    
    /**
    * \brief Возвращает первую точку пересечения, если это возможно
    *
    *
    */
    const Point &FirstPoint();
    
    
    /**
    * \brief Возвращает вторую точку пересечения, если это возможно
    *
    *
    */
    const Point &SecondPoint();
    
    
    /**
     * Возвращает число, равное количеству точек пересечений
     * \return  количество точек пересечений
     */
    int NumberInter();
    
    
    /**
    * \brief Показывает, пересекаются ли кривые или нет
    *
    *
    */
    InterStatus CurrentStatus();
    
    /**
 * \brief Вычисляет точки пересечения окружности с прямой
 * Параметры \f$ a, b, c \f$ из общего уравнения прямой \f$ A x + B y + C = 0 \f$
 * \param r Радиус окружности
 */
    void InterCircleLine(double r, double a, double b, double c);

protected:


/**
 * \brief Находит точки пересечения у двух линий
 * \param line1 Первая линия
 * \param line2 Вторая линия
 */
    void InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Line> &line2);

/**
* \brief Находит точки пересечения у двух окружностей
* \param circle1 Первая окружность
* \param circle2 Вторая окружность
*/
    void InterPoints(const shared_ptr<Circle> &circle1, const shared_ptr<Circle> &circle2);

/**
* \brief Находит точки пересечения у линии и окружности
* \param line1 Линия
* \param circle1 Окружность
*/
    void InterPoints(const shared_ptr<Line> &line1, const shared_ptr<Circle> &circle1);
};


#endif //CURVE_INTERSECTION_H
