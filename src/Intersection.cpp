#include <iostream>
#include <vector>
#include <memory>

#include "Point.h"
#include "Curve.h"
#include "Vector.h"
#include "Straight.cpp"
#include "Circle.cpp"
#include "Intersection.h"


#define M_PI 3.141592653589793
#define EPS 1e-10

// метод нахождения точек пересечения
vector<Points> Intersections::Intersection(shared_ptr<Curve> ptr1, shared_ptr<Curve> ptr2)
	{
		// приведение указателя1 к типу "Прямая"
		shared_ptr<Straight> straightPtr1 = std::dynamic_pointer_cast<Straight>(ptr1);
		if (straightPtr1)
		{
			// приведение указателя2 к типу "Прямая"
			shared_ptr<Straight> straightPtr2 = std::dynamic_pointer_cast<Straight>(ptr2);
			if (straightPtr2)
			{
				// реализация метода - найти точку пересечения 2 прямых
				vector<Points> points;
				Points* firstLinePoint = straightPtr1->PointCalcul(5);
				double firstLinePtX = firstLinePoint->getX();
				double firstLinePtY = firstLinePoint->getY();
				// получение направляющего вектора первой прямой
				double firstDot1 = straightPtr1->getDot1();
				double firstDot2 = straightPtr1->getDot2();

				Points* secondLinePoint = straightPtr2->PointCalcul(3);
				//получение координат второй прямой
				double secondLinePtX = secondLinePoint->getX();
				double secondLinePtY = secondLinePoint->getY();
				// получение направляющего вектора второй прямой
				double secondDot1 = straightPtr2->getDot1();
				double secondDot2 = straightPtr2->getDot2();

				double determinant1 = -secondDot1 - (-firstDot1);
				// решаем систему y-p2*t=y0 ; y-p21*t=y01; determinant1 = 1*(-p21)-(-p2)*1
				double determinant2 = -secondDot2 - (-firstDot2);

				if (determinant1 != 0 && determinant2 != 0)
				{
					points.push_back(Points((firstLinePtX * (-secondDot1) - (-firstDot1 * secondLinePtX)) / determinant1,
						(secondLinePtY - firstLinePtY) / determinant2));
				}
				return points;
			}
			else
			{//приведение указателя2 к типу "круг"
				shared_ptr<Circle> straightPtr2 = std::dynamic_pointer_cast<Circle>(ptr2);
				if (straightPtr2)
				{
					// реализация метода - найти точку/и пересечения прямой и окружности
					vector<Points> points;

					Points* circleCenterPoint = straightPtr2->getCurvePoint();
					//получение координат центра окружности 
					double firstcirclePtX = circleCenterPoint->getX();
					double firstcirclePtY = circleCenterPoint->getY();
					//получение радиуса
					double radius = straightPtr2->getRadius();

					Points* firstLinePoint = straightPtr1->getCurvePoint();
					//получение координат прямой
					double firstLinePtX = firstLinePoint->getX();
					double firstLinePtY = firstLinePoint->getY();
					//получение направляющего вектора прямой
					double firstP1 = straightPtr1->getDot1();
					double firstP2 = straightPtr1->getDot2();

					Points* zeroPoint = straightPtr1->PointCalcul(0.0); // точка на прямой 1
					Points* randomPoint = straightPtr1->PointCalcul(rand() % 10 + 1); // случайная точка на прямой 
					// получение центральной точки на прямой 
					Points middle = Points(zeroPoint->getX() - randomPoint->getX(), zeroPoint->getY() - randomPoint->getY());
					//расстояние от центра окружности до центральной точки
					double distance = abs(middle.getY() * firstcirclePtX + middle.getX() * firstcirclePtY +
						(zeroPoint->getY() * randomPoint->getX() - randomPoint->getY() * zeroPoint->getX())) /
						sqrt(pow(middle.getY(), 2) + pow(middle.getX(), 2));
					// расчет точек 
					if (distance <= radius + EPS)
					{
						points.push_back(Points(2 * asin(distance / radius), 2 * acos(distance / radius)));
						if (distance < radius - EPS)
						{
							points.push_back(Points((2 * asin(distance / radius) - distance), (2 * acos(distance / radius) - distance)));
						}
					}

					return points;
				}
				// нулевой указатель
				else
				{
					cout << "no";
				}
			}
		}
		else
		{
			shared_ptr<Circle> straightPtr1 = std::dynamic_pointer_cast<Circle>(ptr1);
			if (straightPtr1)
			{
				shared_ptr<Straight> straightPtr2 = std::dynamic_pointer_cast<Straight>(ptr2);
				if (straightPtr2)
				{
					// реализация метода - найти точку/и пересечения прямой и окружности
					vector<Points> points;

					Points* circleCenterPoint = straightPtr1->getCurvePoint();
					//получение координат центра окружности 
					double firstcirclePtX = circleCenterPoint->getX();
					double firstcirclePtY = circleCenterPoint->getY();
					//получение радиуса
					double radius = straightPtr1->getRadius();

					Points* firstLinePoint = straightPtr2->getCurvePoint();
					//получение координат прямой
					double firstLinePtX = firstLinePoint->getX();
					double firstLinePtY = firstLinePoint->getY();
					//получение направляющего вектора прямой
					double firstP1 = straightPtr2->getDot1();
					double firstP2 = straightPtr2->getDot2();

					Points* zeroPoint = straightPtr2->PointCalcul(0.0); // точка на прямой 1
					Points* randomPoint = straightPtr2->PointCalcul(rand() % 10 + 1); // случайная точка на прямой 
																					// получение центральной точки на прямой 
					Points middle = Points(zeroPoint->getX() - randomPoint->getX(), zeroPoint->getY() - randomPoint->getY());
					//расстояние от центра окружности до центральной точки
					double distance = abs(middle.getY() * firstcirclePtX + middle.getX() * firstcirclePtY +
						(zeroPoint->getY() * randomPoint->getX() - randomPoint->getY() * zeroPoint->getX())) /
						sqrt(pow(middle.getY(), 2) + pow(middle.getX(), 2));
					// расчет точек 
					if (distance <= (radius-EPS))
					{
						points.push_back(Points(2 * asin(distance / radius), 2 * acos(distance / radius)));
						if (distance < (radius-EPS))
						{
							points.push_back(Points((2 * asin(distance / radius) - distance), (2 * acos(distance / radius) - distance)));
						}
					}

					return points;
				}
				else
				{
					shared_ptr<Circle> straightPtr2 = std::dynamic_pointer_cast<Circle>(ptr2);
					if (straightPtr2)
					{
						//реализация метода - найти точку/и пересечения двух окружностей

						vector<Points> points;

						Points* firstCenterPoint = straightPtr1->getCurvePoint();
						// получение координат первой окружности 
						double firstX = firstCenterPoint->getX();
						double firstY = firstCenterPoint->getY();

						Points* secondCenterPoint = straightPtr2->getCurvePoint();
						// получение координат второй окружности 
						double secondX = secondCenterPoint->getX();
						double secondY = secondCenterPoint->getY();
						//получение радиусов
						double firstRadius = straightPtr1->getRadius();
						double secondRadius = straightPtr2->getRadius();
						//расстояние между центрами окружностей
						double distance = sqrt(pow((firstX - secondX), 2) + pow((firstY - secondY), 2));
						// исключение концентрических окружностей (окружности с одинаковой начальной точкой)
						if (secondX == firstX && firstY == secondY && firstRadius == secondRadius)
						{
							cout << "совпадают окружности";
						}
						else
						{
							if (secondX == firstX && firstY == secondY && firstRadius != secondRadius)
							{
								cout << "нет точек пересечения";
							}
							else
							{
								if (distance <= firstRadius + secondRadius)
								{
									// Первая точка
									points.push_back(Points(acos(((secondX - firstX) / (firstRadius - secondRadius))),
										asin((secondY - firstY) / (firstRadius - secondRadius))));

									//Вторая точка
									if (distance < (firstRadius + secondRadius))
									{
										points.push_back(Points(M_PI - acos(((secondX - firstX) / (firstRadius - secondRadius))),
											M_PI - asin((secondY - firstY) / (firstRadius - secondRadius))));
									}
								}
							}
							return points;
						}
					}
					else
						cout << "no";
				}
			}
		}
	}
