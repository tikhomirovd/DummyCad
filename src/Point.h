//
// Created by dimas on 4/12/19.
//

#ifndef CURVE_POINT_H
#define CURVE_POINT_H

#include <Curve_def.h>


using namespace std;

/**
 * \brief Класс, который задаёт точку \f$ M \f$.
 */
class Curve_EXPORT Point
{
private:
    double myCoordX = 0, myCoordY = 0, myCoordZ = 0;


public:
    Point();
    
    explicit Point(double);
    
    Point(double, double);
    
    Point(double, double, double);
    
    /**
     * \brief Присваивает точке заданные координаты
     * \param x  координата \f$ M_x \f$
     * \param y  координата \f$ M_y \f$
     * \param z  координата \f$ M_z \f$
     */
    void SetCoord(double, double, double);
    
    /**
     * Возвращает координату \f$ x \f$ у точки
     * \return \f$ M_x \f$
     */
    double X() const;
    
    /**
     * Возвращает координату \f$ y \f$ у точки
     * \return \f$ M_y \f$
     */
    double Y() const;
    
    /**
     * Возвращает координату \f$ z \f$ у точки
     * \return \f$ M_z \f$
     */
    double Z() const;
    
    /**
     * Нормализует вектор
     */
    void Normalize();
    
    /**
     * Перегрузка оператора "+". Складывает точки покоординатно
     * \param a Точка \f$ A \f$
     * \param b Точка \f$ B \f$
     * \return  Точка \f$ \{A_x + B_x, A_y + B_y, A_z + B_z \} \f$
     */
    friend const Point operator+(const Point &a, const Point &b)
    {
        
        return {a.X() + b.X(), a.Y() + b.Y(), a.Z() + b.Z()};
    }
    
    /**
    * Перегрузка оператора "-". Вычитает точки покоординатно
    * \param a Точка \f$ A \f$
    * \param b Точка \f$ B \f$
    * \return  Точка \f$ \{A_x - B_x, A_y - B_y, A_z - B_z \} \f$
    */
    friend const Point operator-(const Point &a, const Point &b)
    {
        
        return {a.X() - b.X(), a.Y() - b.Y(), a.Z() - b.Z()};
    }
    
    /**
     * Перегрузка оператора "*". Умножение вектора на число
     * \param a Точка \f$ A \f$
     * \param i Скаляр \f$ i \f$
     * \return  Точка \f$ \{A_x * i, A_y * i, A_z * i \} \f$
     */
    friend const Point operator*(const Point &a, const double &i)
    {
        
        return {a.X() * i, a.Y() * i, a.Z() * i};
    }
    
    /**
     * Перегрузка оператора "+". Прибавление к вектору число покоординатно
     * \param a Точка \f$ A \f$
     * \param i Скаляр  \f$ i \f$
     * \return  Точка \f$ \{A_x + i, A_y + i, A_z + i\} \f$
     */
    friend const Point operator+(const Point &a, const double &i)
    {
        
        return {a.X() + i, a.Y() + i, a.Z() + i};
    }
    
    
};


#endif //CURVE_POINT_H
