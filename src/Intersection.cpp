#include <iostream>
#include <vector>
#include <memory>
#include <math.h>

#include "Point.h"
#include "Curve.h"
#include "Vector.h"
#include "Straight.cpp"
#include "Circle.cpp"
#include "Intersection.h"


#define M_PI 3.141592653589793
#define EPS 1e-10

// метод нахождения точек пересечения
vector<Point> Intersections::Intersection(shared_ptr<Curve> ptr1, shared_ptr<Curve> ptr2)
{
  std::vector<Point> result;

  // приведение указателя1 к типу "Прямая"
  shared_ptr<Straight> straightPtr1 = std::dynamic_pointer_cast<Straight>(ptr1);
  if (straightPtr1)
  {
    // приведение указателя2 к типу "Прямая"
    shared_ptr<Straight> straightPtr2 = std::dynamic_pointer_cast<Straight>(ptr2);
    if (straightPtr2)
    {
      result = SolveLineLine(straightPtr1, straightPtr2);
    }
    else
    {
      //приведение указателя2 к типу "круг"
      shared_ptr<Circle> Circle2 = std::dynamic_pointer_cast<Circle>(ptr2);
      if (Circle2)
      {
        result = SolveCircleLine(Circle2, straightPtr1);
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
    shared_ptr<Circle> Circle1 = std::dynamic_pointer_cast<Circle>(ptr1);
    if (Circle1)
    {
      shared_ptr<Straight> straightPtr2 = std::dynamic_pointer_cast<Straight>(ptr2);
      if (straightPtr2)
      {
        result = SolveCircleLine(Circle1, straightPtr2);
      }
      else
      {
        shared_ptr<Circle> Circle2 = std::dynamic_pointer_cast<Circle>(ptr2);
        if (Circle2)
        {
          result = SolveCircleCircle(Circle1, Circle2);
        }
        else
          cout << "no";
      }
    }
  }

  return result;
}


vector<Point> Intersections::SolveLineLine(shared_ptr<Straight> ptr1, shared_ptr<Straight> ptr2)
{
  // реализация метода - найти точку пересечения 2 прямых
  vector<Point> points;

  //Point* firstLinePoint = straightPtr1->PointCalcul(5);
  Point* firstLinePoint = ptr1->getCurvePoint();
  double firstLinePtX = firstLinePoint->getX();
  double firstLinePtY = firstLinePoint->getY();
  // получение направляющего вектора первой прямой
  double firstDot1 = ptr1->getDot1();
  double firstDot2 = ptr1->getDot2();

  //Point* secondLinePoint = straightPtr2->PointCalcul(3);
  Point* secondLinePoint = ptr2->getCurvePoint();
  //получение координат второй прямой
  double secondLinePtX = secondLinePoint->getX();
  double secondLinePtY = secondLinePoint->getY();
  // получение направляющего вектора второй прямой
  double secondDot1 = ptr2->getDot1();
  double secondDot2 = ptr2->getDot2();

  double determinant1 = secondDot1 - firstDot1;
  // решаем систему y-p2*t=y0 ; y-p21*t=y01; determinant1 = 1*(-p21)-(-p2)*1
  double determinant2 = secondDot2 - firstDot2;

  if (determinant1 != 0 && determinant2 != 0)
  {
    points.push_back(Point((firstLinePtX * (secondDot1)-(firstDot1 * secondLinePtX)) / determinant1,
      (firstLinePtY*firstDot1 - firstDot2* secondLinePtY) / determinant2));
  }
  return points;
}

vector<Point> Intersections::SolveCircleCircle(shared_ptr<Circle> ptr1, shared_ptr<Circle> ptr2)
{
  //реализация метода - найти точку/и пересечения двух окружностей

  vector<Point> points;

  Point* firstCenterPoint = ptr1->getCurvePoint();
  // получение координат первой окружности 
  double firstX = firstCenterPoint->getX();
  double firstY = firstCenterPoint->getY();

  Point* secondCenterPoint = ptr2->getCurvePoint();
  // получение координат второй окружности 
  double secondX = secondCenterPoint->getX();
  double secondY = secondCenterPoint->getY();

  //получение радиусов
  double firstRadius = ptr1->getRadius();
  double secondRadius = ptr2->getRadius();
  double summRadius = firstRadius + secondRadius;
  double differenceRadius = firstRadius - secondRadius;

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
      if (distance>summRadius + EPS || distance<differenceRadius - EPS)
      {
        cout << "no solution";
      }
      else
        double si = abs(distance - firstRadius + secondRadius);
        if (abs(distance - summRadius) < EPS || abs(distance - differenceRadius)<EPS)
        {
          // 1 решение
          // получение точки решения
          double middlepoint1 = (firstX + secondX) / 2;
          double middlepoint2 = (firstY + secondY) / 2;
          Point* d = new Point(middlepoint1, middlepoint2);
          points.push_back(Point(d->getX(), d->getY()));
        }
        else
        {
          // 2 решения
          // получение серединной точки на прямой
          double middlepoint1 = (firstX + secondX) / 2;
          double middlepoint2 = (firstY + secondY) / 2;
          Point* d = new Point(middlepoint1, middlepoint2);
          // получение разности координат
          double coordinate1 = firstX - secondX;
          double coordinate2 = firstY - secondY;
          // координаты направляющего вектора на первой прямой
          Point* vector1 = new Point(-coordinate1, -coordinate2);
          // координаты направлябщего вектора прямой, через которую будут искаться решения
          Point* vector2 = new Point(-coordinate2, coordinate1);
          // прямая, проходящая через найденную точку и через которую будут искаться решения
          Straight* straight = new Straight(middlepoint1, middlepoint2, vector2->getX(), vector2->getY());
          shared_ptr<Curve> strai = shared_ptr<Straight>(new Straight(middlepoint1, middlepoint2, vector2->getX(), vector2->getY()));
          std::vector<Point> points1 = Intersection(strai, ptr1);
          std::vector<Point> points2 = Intersection(strai, ptr2);
          points.push_back(Point(points1[0].getX(), points1[0].getY()));
          points.push_back(Point(points1[1].getX(), points1[1].getY()));
        }

      }
    }
    return points;
}

vector<Point> Intersections::SolveCircleLine(shared_ptr<Circle> ptr1, shared_ptr<Straight> ptr2)
{
  // реализация метода - найти точку/и пересечения прямой и окружности
  vector<Point> points;

  Point* circleCenterPoint = ptr1->getCurvePoint();
  //получение координат центра окружности 
  double firstcirclePtX = circleCenterPoint->getX();
  double firstcirclePtY = circleCenterPoint->getY();
  //получение радиуса
  double radius = ptr1->getRadius();
  // получение точек прямой
  Point* firstLinePoint = ptr2->getCurvePoint();
  //получение координат прямой
  double firstLinePtX = firstLinePoint->getX();
  double firstLinePtY = firstLinePoint->getY();
  //получение направляющего вектора прямой
  double firstP1 = ptr2->getDot1();
  double firstP2 = ptr2->getDot2();
  //нормализация направляющего вектора
  Vector vector2 = Vector(firstP1, firstP2);
  Vector z = vector2.Normalize();
  // новый вектор 
  Vector vector = Vector(firstcirclePtX - firstLinePtX, firstcirclePtY - firstLinePtY);

  //вычисление декартового произведения
  double decartDot = vector.getX()*z.getX() + vector.getY()*z.getY();
  //спроецированный радиус на прямую - точка на прямой
  Point A = Point(firstLinePtX + decartDot*z.getX(), firstLinePtY + decartDot*z.getY());
  // новая прямая с начальной найденной точкой и нормализированным направлением
  Straight* str = new Straight (A.getX(),A.getY(),z.getX(),z.getY());
  // длина от центра до новой точки на прямой
  double distance = sqrt(pow(A.getX() - firstcirclePtX, 2) + pow(A.getY() - firstcirclePtY, 2));
  // длина он начальной точки прямой до найденной
  double rastDot = sqrt(pow(radius, 2) - pow(distance, 2));
  if (distance == 0 || distance==radius)
  {
    // прямая проходит через центр окружности - 2 точки
    if (distance == 0)
    {
       Point* ty = str->PointCalcul(radius);
       Point* ty2 = str->PointCalcul(-radius);
       points.push_back(Point(ty->getX(), ty->getY()));
       points.push_back(Point(ty2->getX(), ty2->getY()));
    } 
    // одна точка на прямой       
    if (distance == radius)
       {
          Straight* str1 = new Straight(firstLinePtX, firstLinePtY, z.getX(), z.getY());
          Point* ty = str1->PointCalcul(-decartDot);
          points.push_back(Point(ty->getX(), ty->getY()));
       }
  }

  else
  {   // две точки пересечения
      if (distance <= radius + EPS)
      {
        // находим координаты на нашей прямой в точке 1
        Point* parameter = str->PointCalcul(1);
        // расчитывает расстояние от найденной точки до центра заданной окружности
        double distance = sqrt(pow(parameter->getX() - firstcirclePtX, 2) + pow(parameter->getY() - firstcirclePtY, 2));
        // находим расстояние от начальной точки до точки на прямой
        double rastDotParametr = sqrt(pow(radius, 2) - pow(distance, 2));
        // вычисляем параметр через соотношение через который найдем точки пересечения 
        double parametr2 = rastDot/ rastDotParametr;
        // ищем точку с найденным параметром
        Point* point1 = str->PointCalcul(parametr2);
        points.push_back(Point(point1->getX(),point1->getY()));
          if (rastDot < radius + EPS)
          {
            Point* point2 = str->PointCalcul(-parametr2);
            points.push_back(Point(point2->getX(), point2->getY()));
          }
    
      } 
  }   
  return points;
}
