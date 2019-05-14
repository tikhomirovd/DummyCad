#include <iostream>
#include <vector>
#include <memory>
#include <math.h>

#include <Point.h>
#include <Curve.h>
#include <Vector.h>
#include <Line.cpp>
#include <Circle.cpp>
#include <Intersection.h>


static const double M_PI = 3.141592653589793;
static const double EPS = 1.e-10;


bool pqw = true;
// метод нахождения точек пересечения
Vector Intersections::Intersection(std::shared_ptr<Curve> ptr1, std::shared_ptr<Curve> ptr2)
{
  std::vector<Point> result;

  // приведение указателя1 к типу "Прямая"
  std::shared_ptr<Line> straightPtr1 = std::dynamic_pointer_cast<Line>(ptr1);
  if (straightPtr1)
  {
    // приведение указателя2 к типу "Прямая"
    std::shared_ptr<Line> straightPtr2 = std::dynamic_pointer_cast<Line>(ptr2);
    if (straightPtr2)
    {
      result = SolveLineLine(straightPtr1, straightPtr2);
    }
    else
    {
      //приведение указателя2 к типу "Круг"
      std::shared_ptr<Circle> Circle2 = std::dynamic_pointer_cast<Circle>(ptr2);
      if (Circle2)
      {
        result = SolveCircleLine(Circle2, straightPtr1);
      }
      // нулевой указатель
      else
      {
        return Circle2->TF();
      }
    }
  }
  else
  {
    // приведение указателя1 к типу "Круг"
    std::shared_ptr<Circle> Circle1 = std::dynamic_pointer_cast<Circle>(ptr1);
    if (Circle1)
    {
      // приведение указателя2 к типу "Прямая"
      std::shared_ptr<Line> straightPtr2 = std::dynamic_pointer_cast<Line>(ptr2);
      if (straightPtr2)
      {
        result = SolveCircleLine(Circle1, straightPtr2);
      }
      else
      {
        //приведение указателя2 к типу "Круг"
        std::shared_ptr<Circle> Circle2 = std::dynamic_pointer_cast<Circle>(ptr2);
        if (Circle2)
        {
          result = SolveCircleCircle(Circle1, Circle2);
        }
        else
          /*try {
          throw MathematicError();
        }
        catch (...) {
          return !pqw;
          throw;
        } */
           return Circle2->TF();
      }
    }
  }

  return result;
}


std::vector<Point> Intersections::SolveLineLine(std::shared_ptr<Line> ptr1, std::shared_ptr<Line> ptr2)
{
  // реализация метода - найти точку пересечения 2 прямых
  std::vector<Point> points;

  Vector firstLinePoint = ptr1->getCurvePoint();
  double firstLinePtX = firstLinePoint.getX();
  double firstLinePtY = firstLinePoint.getY();
  // получение направляющего вектора первой прямой
  double firstDot1 = ptr1->getDot1();
  double firstDot2 = ptr1->getDot2();

  Vector secondLinePoint = ptr2->getCurvePoint();
  //получение координат второй прямой
  double secondLinePtX = secondLinePoint.getX();
  double secondLinePtY = secondLinePoint.getY();
  // получение направляющего вектора второй прямой
  double secondDot1 = ptr2->getDot1();
  double secondDot2 = ptr2->getDot2();
  // ищем детерминанты
  double determinant1 = secondDot1 - firstDot1;
  // решаем систему y-p2*t=y0 ; y-p21*t=y01; determinant1 = 1*(-p21)-(-p2)*1
  double determinant2 = secondDot2 - firstDot2;

  if (determinant1 != EPS && determinant2 != EPS)
  {
    points.push_back(Point((firstLinePtX * (secondDot1)-(firstDot1 * secondLinePtX)) / determinant1,
      (firstLinePtY*firstDot1 - firstDot2* secondLinePtY) / determinant2));
  }
  return points;
}

std::vector<Point> Intersections::SolveCircleCircle(std::shared_ptr<Circle> ptr1, std::shared_ptr<Circle> ptr2)
{
  //реализация метода - найти точку/и пересечения двух окружностей

  std::vector<Point> points;

  Vector firstCenterPoint = ptr1->getCurvePoint();
  // получение координат первой окружности 
  double firstX = firstCenterPoint.getX();
  double firstY = firstCenterPoint.getY();

  Vector secondCenterPoint = ptr2->getCurvePoint();
  // получение координат второй окружности 
  double secondX = secondCenterPoint.getX();
  double secondY = secondCenterPoint.getY();

  //получение радиусов
  double firstRadius = ptr1->getRadius();
  double secondRadius = ptr2->getRadius();
  //создаем переменные для суммы и разности радиусов
  double sumRadius = firstRadius + secondRadius;
  double differenceRadius = fabs(firstRadius - secondRadius);

  //расстояние между центрами окружностей
  double distance = sqrt(pow((firstX - secondX), 2) + pow((firstY - secondY), 2));

  // исключение концентрических окружностей (окружности с одинаковой начальной точкой)
  if (secondX+EPS == firstX+EPS && firstY+EPS == secondY+EPS && firstRadius+EPS == secondRadius+EPS)
  {
    points.push_back(Point(0, 0));
  }
  else
  {
    if (secondX + EPS == firstX + EPS && firstY + EPS == secondY + EPS && firstRadius + EPS != secondRadius + EPS)
    {
      // совпадают окружности
      return ptr1->Coincidence();
    }
    else
    {
      if (distance > sumRadius + EPS || distance < differenceRadius - EPS)
      {
        // нет пересечения
        return ptr1->NoIntersection();
      }
      else
      {
        double si = fabs(distance - firstRadius + secondRadius);
        if (fabs(distance - sumRadius) < EPS || fabs(distance - differenceRadius) < EPS)
        {
          // 1 решение
          // получение среднего значения суммы координат
          double middlepoint1 = (firstX + secondX) / 2;
          double middlepoint2 = (firstY + secondY) / 2;
          // получаем разность координат
          double coordinate1 = firstX - secondX;
          double coordinate2 = firstY - secondY;
          // формирует точку - направление
          Vector vector1 = Vector(-coordinate1, -coordinate2);
          // новая прямая записанная через умный указатель
          std::shared_ptr<Curve> strai = std::shared_ptr<Line>(new Line(middlepoint1, middlepoint2, vector1.getX(), vector1.getY()));
          // вычисление точек на прямой, которая пересекает каждую из окружностей
          std::vector<Point> points1 = Intersection(strai, ptr1);
          std::vector<Point> points2 = Intersection(strai, ptr2);
          // сравнение полученных координат - ищем общую и её записываем в ответ
          if (((points1[0].getX()==points2[0].getX()) && points1[0].getY()==points2[0].getY()) || (points1[0].getX() == points2[1].getX()) && points1[0].getY() == points2[1].getY())
          {
            points.push_back(Point(points1[0].getX(), points1[0].getY()));
          }
          else 
          {
             if ((points1[1].getX() == points2[1].getX() && points1[1].getX()==points2[1].getY()) || (points1[1].getX() == points2[0].getX() && points1[1].getY() == points2[0].getY()))
             {
               points.push_back(Point(points1[1].getX(), points1[1].getY()));
             }
          }
        }
        else
        {
          // 2 решения
          // получение серединной точки на прямой
          double middlepoint1 = (firstX + secondX) / 2;
          double middlepoint2 = (firstY + secondY) / 2;
          Point d = Point(middlepoint1, middlepoint2);
          // получение разности координат
          double coordinate1 = firstX - secondX;
          double coordinate2 = firstY - secondY;
          // координаты направляющего вектора на первой прямой
          Vector vector1 = Vector(-coordinate1, -coordinate2);
          // координаты направлябщего вектора прямой, через которую будут искаться решения
          Vector vector2 = Vector(-coordinate2, coordinate1);
          // создаем умный указатель на неё и передаем вычисленные значения
          std::shared_ptr<Curve> strai = std::shared_ptr<Line>(new Line(middlepoint1, middlepoint2, vector2.getX(), vector2.getY()));
          // вычисляем точки пересечения прямой с этими окружностями
          std::vector<Point> points1 = Intersection(strai, ptr1);
          std::vector<Point> points2 = Intersection(strai, ptr2);
          // добавляем из первой, т.к. точки одинаковы
          points.push_back(Point(points1[0].getX(), points1[0].getY()));
          points.push_back(Point(points1[1].getX(), points1[1].getY()));
        }
      }
    }
  }
  return points;
}

std::vector<Point> Intersections::SolveCircleLine(std::shared_ptr<Circle> ptr1, std::shared_ptr<Line> ptr2)
{
  // реализация метода - найти точку/и пересечения прямой и окружности
  std::vector<Point> points;

  Vector circleCenterPoint = ptr1->getCurvePoint();
  //получение координат центра окружности 
  double firstcirclePtX = circleCenterPoint.getX();
  double firstcirclePtY = circleCenterPoint.getY();
  //получение радиуса
  double radius = ptr1->getRadius();
  // получение точек прямой
  Vector firstLinePoint = ptr2->getCurvePoint();
  //получение координат прямой
  double firstLinePtX = firstLinePoint.getX();
  double firstLinePtY = firstLinePoint.getY();
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
  Line* str =new Line(A.getX(), A.getY(), z.getX(), z.getY());
  // длина от центра до новой точки на прямой
  double distance = sqrt(pow(A.getX() - firstcirclePtX, 2) + pow(A.getY() - firstcirclePtY, 2));
  // длина он начальной точки прямой до найденной
  double rastDot = sqrt(pow(radius, 2) - pow(distance, 2));
  if (distance == 0 || distance == radius)
  {
    // прямая проходит через центр окружности - 2 точки
    if (distance == 0)
    {
      Point ty = str->PointCalcul(radius);
      Point ty2 = str->PointCalcul(-radius);
      points.push_back(Point(ty.getX(), ty.getY()));
      points.push_back(Point(ty2.getX(), ty2.getY()));
    }
    // одна точка на прямой       
    if (distance == radius)
    {
      Line* str1 = new Line(firstLinePtX, firstLinePtY, z.getX(), z.getY());
      Point ty = str1->PointCalcul(-decartDot);
      points.push_back(Point(ty.getX(), ty.getY()));
    }
  }

  else
  {   // две точки пересечения
    if (distance <= radius + EPS)
    {
      // находим координаты на нашей прямой в точке 1
      Point parameter = str->PointCalcul(1);
      // расчитывает расстояние от найденной точки до центра заданной окружности
      double distance = sqrt(pow(parameter.getX() - firstcirclePtX, 2) + pow(parameter.getY() - firstcirclePtY, 2));
      // находим расстояние от начальной точки до точки на прямой
      double rastDotParametr = sqrt(pow(radius, 2) - pow(distance, 2));
      // вычисляем параметр через соотношение через который найдем точки пересечения 
      double parametr2 = rastDot / rastDotParametr;
      // ищем точку с найденным параметром
      Point point1 = str->PointCalcul(parametr2);
      points.push_back(Point(point1.getX(), point1.getY()));
      if (rastDot < radius + EPS)
      {
        Point point2 = str->PointCalcul(-parametr2);
        points.push_back(Point(point2.getX(), point2.getY()));
      }
    }
  }
  return points;
}
