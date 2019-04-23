//
// Created by dimas on 4/12/19.
//

#ifndef CURVE_CIRCLE_H
#define CURVE_CIRCLE_H


#include "Point.h"
#include "Curve.h"
#include <cmath>

/**
 * \brief Класс "Окружность"
 *
 * Данный класс задаёт окружность. Наследуется от абстрактного класса "Кривая"
 */
class Curve_EXPORT Circle : public Curve {
private:
    Point center;
    double radius = 0;


public:
    Circle() : Curve() {}

    /**
     * \brief Начальная инициализация класса
     *
     * @param ccenter  Центр окружности
     * @param r Радиус окружности
     */
    Circle(Point ccenter, double r);

    /**
     *\brief Вычисляет координаты точки на окружности по заданному парметру
     *
     * @param t Параметр, по которому надо вычислить координаты
     * @return \f$ \{x + r * sin t, y + r * cos t, z \} \f$
     */
    Point Value(double t) override;

    /** \brief Проверяет, является ли кривая замкнутой?
     *
     *
     */
    bool isClosed() override;

    /** \brief Возвращает радиус окружности
     *
     * @return Радиус
     */
    double Radius();

    /** \brief Вычисляет касательный вектор к окружности по заданному параметру
     *
     * @param t Параметр, по которому надо вычислить касательную к окружности
     * @return \f$ \{r * cos t, - r * sin t, 0 \} \f$
     */
    Point tangent(double t) override;


    /** \brief Возвращает координаты центра окружности
  *
  * @return Центр окружности
  */
    Point Center();


};


#endif //CURVE_CIRCLE_H
