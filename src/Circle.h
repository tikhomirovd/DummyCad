//
// Created by dimas on 4/12/19.
//

#ifndef CURVE_CIRCLE_H
#define CURVE_CIRCLE_H


#include <Point.h>
#include <Curve.h>
#include <cmath>

/**
 * \brief Класс "Окружность"
 *
 * Данный класс задаёт окружность.
 */
class Curve_EXPORT Circle : public Curve
{
private:
    Point myCenter;
    double myRadius = 0;


public:
    
    
    /**
     * \brief Начальная инициализация класса
     *
     * \param theCenter  Центр окружности
     * \param theRadius Радиус окружности
     */
    Circle(const Point &theCenter, double theRadius);
    
    /**
     *\brief Вычисляет координаты точки на окружности по заданному парметру
     *
     * \param t Параметр, по которому надо вычислить координаты
     * \return \f$ \{x + r  \cos t, y + r  \sin t, z \} \f$
     */
    Point Value(double t) const override;
    
    /** \brief Проверяет, является ли кривая замкнутой?
     *
     *
     */
    bool IsClosed() const override;
    
    /** \brief Возвращает радиус окружности
     *
     *  \return Радиус
     */
    double Radius();
    
    /** \brief Вычисляет касательный вектор к окружности по заданному параметру
     *
     *  \param t Параметр, по которому надо вычислить касательную к окружности
     *  \return \f$ \{-r \sin t, r \cos t, 0 \} \f$
     */
    Point Tangent(double t) const override;
    
    
    /** \brief Возвращает координаты центра окружности
     *
     * \return Центр окружности
     */
    const Point &Center() const;
    
    
};


#endif //CURVE_CIRCLE_H
