//
// Created by dimas on 4/12/19.
//

#ifndef CURVE_LINE_H
#define CURVE_LINE_H


#include <Curve.h>
#include <Point.h>


/**
 * \brief Класс, который задаёт линию.
 */
class Curve_EXPORT Line : public Curve
{
private:
    Point myCenter, myDirect;


public:

    
    /**
    * \brief Начальная инициализация класса
    *
    * \param a Произвольная точка M1
    * \param b Направляющий вектор
    */
    Line(const Point &, const Point &);
    
    /**
   *\brief Вычисляет координаты точки на прямой по заданному парметру
   *
   * \param t Параметр, по которому надо вычислить координаты
   * \return \f$ \overline{M} = \overline{M_0} + \overline{d} * t \f$
   */
    Point Value(double) override;
    
    /** \brief Проверяет, является ли кривая замкнутой?
     *
     *
     */
    bool IsClosed() override;
    
    /** \brief Вычисляет касательный вектор к линии по заданному параметру
    * d - Направляющий вектор
    * \param t Параметр, по которому надо вычислить касательную к линии
    * \return \f$ \overline{d} \f$
    */
    Point Tangent(double t) override;
    
    /**
     * \brief По параметрическому уравнению выдаёт коэффициенты из общего уравнения
     * В нашем случае прямая задаётся параметрически. \\
     * Функция переделывает уравнение прямой в общее - \f$ A x + B y + C = 0 \f$ и возвращает вектор
     * \f$ \{A, B, C \} \f$
     * \return Вектор \f$ \{A, B, C \} \f$
     */
    Point CoefEquation();
};


#endif //CURVE_LINE_H
