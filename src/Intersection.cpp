#include <vector>
#include <memory>
#include <math.h>

#include <Point.h>
#include <Curve.h>
#include <Vector.h>
#include <Intersection.h>
#include <Line.h>
#include <Circle.h>

static const double M_PI = 3.141592653589793;
static const double EPS = 1.e-10;


// метод нахождения точек пересечения
CalculationResult* Intersections::Intersection(std::shared_ptr<Curve> ptr1, std::shared_ptr<Curve> ptr2)
{
  std::vector<Point> result;
  CalculationResult *t;

  // приведение указателя1 к типу "Прямая"
  std::shared_ptr<Line> straightPtr1 = std::dynamic_pointer_cast<Line>(ptr1);
  std::shared_ptr<Line> straightPtr2 = std::dynamic_pointer_cast<Line>(ptr2);
  std::shared_ptr<Circle> Circle1 = std::dynamic_pointer_cast<Circle>(ptr1);
  std::shared_ptr<Circle> Circle2 = std::dynamic_pointer_cast<Circle>(ptr2);

    if (straightPtr1 && straightPtr2) {
      return SolveLineLine(straightPtr1, straightPtr2);
  }
    if (straightPtr1 && Circle2) {
      return SolveCircleLine(Circle2, straightPtr1);
}
    if (Circle1 && straightPtr2) {
      return SolveCircleLine(Circle1, straightPtr2);
    }
    if (Circle1 && Circle2) {
      return SolveCircleCircle(Circle1, Circle2);
    }
    t = new CalculationResult(UNSUPPORTED_CURVE);
    return t;
}


CalculationResult* Intersections::SolveLineLine(std::shared_ptr<Line> ptr1, std::shared_ptr<Line> ptr2)
{
  // реализация метода - найти точку пересечения 2 прямых
  std::vector<Point> point;
  CalculationResult *t = new CalculationResult();

  Point firstLinePoint = ptr1->getCurvePoint();
  // получение направляющего вектора первой прямой
  Vector direction1 = Vector (ptr1->getDot1(), ptr1->getDot2());

  Point secondLinePoint = ptr2->getCurvePoint();
  // получение направляющего вектора второй прямой
  Vector direction2 = Vector(ptr2->getDot1(), ptr2->getDot2());
  // ищем детерминанты
  double determinant1 = direction2.getX() - direction1.getX();
  // решаем систему y-p2*t=y0 ; y-p21*t=y01; determinant1 = 1*(-p21)-(-p2)*1
  double determinant2 = direction2.getY() - direction1.getY();
  //определяем разность дискриминантов и сравниваем с допуском
if (fabs(firstLinePoint.getX()- secondLinePoint.getX())<EPS && fabs(firstLinePoint.getY() - secondLinePoint.getY())
&& fabs(direction1.getX() - direction2.getX())<EPS && fabs(direction1.getY() - direction2.getY()))
{
  return new CalculationResult(COINCIDENCE);
}
  if (fabs(determinant1) > EPS && fabs(determinant2) > EPS)
  {
    // расчитываем координаты точки пересечения для двух линий через определители матрицы 
    point.push_back(Point((firstLinePoint.getX() * (direction2.getX())-(direction1.getX() * secondLinePoint.getX())) / determinant1,
      (firstLinePoint.getY()*direction1.getX() - direction1.getY()* secondLinePoint.getY()) / determinant2));
    t->solution = point;
    t->type = SOLUTION;
    return t;
  } // если один из них равен 0, то точки пересечения нет
  if (fabs(determinant1) < EPS && fabs(determinant2) < EPS)
  {
    t->type = NO_INTERSECTION;
    return t;
  }
}

CalculationResult* Intersections::SolveCircleCircle(std::shared_ptr<Circle> ptr1, std::shared_ptr<Circle> ptr2)
{
  //реализация метода - найти точку/и пересечения двух окружностей

  std::vector<Point> points;
  CalculationResult *t;

  Point firstCenterPoint = ptr1->getCurvePoint();

  Point secondCenterPoint = ptr2->getCurvePoint();

  //получение радиусов
  double firstRadius = ptr1->getRadius();
  double secondRadius = ptr2->getRadius();
  //создаем переменные для суммы и разности радиусов
  double sumRadius = firstRadius + secondRadius;

  double deltaX = fabs(firstCenterPoint.getX() - secondCenterPoint.getX());
  double deltaY = fabs(firstCenterPoint.getY() - secondCenterPoint.getY());
  double deltaR = fabs(firstRadius - secondRadius);

  //расстояние между центрами окружностей
  double distance = sqrt(pow((firstCenterPoint.getX() - secondCenterPoint.getX()), 2) + pow((firstCenterPoint.getY() - secondCenterPoint.getY()), 2));

  // исключение концентрических окружностей (окружности с одинаковой начальной точкой)
  if (deltaX + deltaY + deltaR < EPS) {
   return new CalculationResult(COINCIDENCE);
  }

  if (
    //в одной точке с разным радиусом
      (deltaX + deltaY < EPS && deltaR > EPS) || 
    //круг вне круга или круг внутри круга
    (distance > sumRadius + EPS || distance < deltaR - EPS)
    ) {
    return new CalculationResult(NO_INTERSECTION);
  }

        if (fabs(distance - sumRadius) < EPS || fabs(distance - deltaR) < EPS)
        {
          // 1 решение
          // получение среднего значения суммы координат
          double middlepoint1 = (firstCenterPoint.getX() + secondCenterPoint.getX()) / 2;
          double middlepoint2 = (firstCenterPoint.getY() + secondCenterPoint.getY()) / 2;
          // получаем разность координат
          double coordinate1 = firstCenterPoint.getX() - secondCenterPoint.getX();
          double coordinate2 = firstCenterPoint.getY() - secondCenterPoint.getY();
          // формирует точку - направление
          Vector vector1 = Vector(-coordinate1, -coordinate2);
          // новая прямая записанная через умный указатель
          std::shared_ptr<Curve> strai = std::shared_ptr<Line>(new Line(middlepoint1, middlepoint2, vector1.getX(), vector1.getY()));
          // вычисление точек на прямой, которая пересекает каждую из окружностей
          CalculationResult* points1 = Intersection(strai, ptr1);
          CalculationResult* points2 = Intersection(strai, ptr2);
          // сравнение полученных координат - ищем общую и её записываем в ответ
          if ((points1->solution[0]==points2->solution[0]) || (points1->solution[0] == points2->solution[1]))
          {
            points.push_back(Point(points1->solution[0].getX(), points1->solution[0].getX()));
            t = new CalculationResult(COINCIDENCE);
            t->solution = points;
            return t;
          }
          if ((points1->solution[1] == points2->solution[1]) || (points1->solution[1] == points2->solution[0]))
           {
             points.push_back(Point(points1->solution[1].getX(), points1->solution[1].getY()));
             t = new CalculationResult(COINCIDENCE);
             t->solution = points;
             return t;
           }
        }

        else
        {
          // 2 решения
          // получение серединной точки на прямой
          double middlepoint1 = (firstCenterPoint.getX() + secondCenterPoint.getX()) / 2;
          double middlepoint2 = (firstCenterPoint.getY() + secondCenterPoint.getY()) / 2;
          Point d = Point(middlepoint1, middlepoint2);
          // получение разности координат
          double coordinate1 = firstCenterPoint.getX() - secondCenterPoint.getX();
          double coordinate2 = firstCenterPoint.getY() - secondCenterPoint.getY();
          // координаты направляющего вектора на первой прямой
          Vector vector1 = Vector(-coordinate1, -coordinate2);
          // координаты направлябщего вектора прямой, через которую будут искаться решения
          Vector vector2 = Vector(-coordinate2, coordinate1);
          // создаем умный указатель на неё и передаем вычисленные значения
          std::shared_ptr<Curve> strai = std::shared_ptr<Line>(new Line(middlepoint1, middlepoint2, vector2.getX(), vector2.getY()));
          // вычисляем точки пересечения прямой с этими окружностями
          CalculationResult* points1 = Intersection(strai, ptr1);
          CalculationResult* points2 = Intersection(strai, ptr2);
          // добавляем из первой, т.к. точки одинаковы
          points.push_back(Point(points1->solution[0].getX(), points1->solution[0].getY()));
          points.push_back(Point(points1->solution[1].getX(), points1->solution[1].getY()));
          t = new CalculationResult(COINCIDENCE);
          t->solution = points;
          return t;
        }};


CalculationResult* Intersections::SolveCircleLine(std::shared_ptr<Circle> ptr1, std::shared_ptr<Line> ptr2)
{
  // реализация метода - найти точку/и пересечения прямой и окружности
  std::vector<Point> points;
  CalculationResult *t;

  Point circleCenterPoint = ptr1->getCurvePoint();
  //получение радиуса
  double radius = ptr1->getRadius();
  // получение точек прямой
  Point firstLinePoint = ptr2->getCurvePoint();
  //получение координат прямой
  double firstLinePtX = firstLinePoint.getX();
  double firstLinePtY = firstLinePoint.getY();
  //получение направляющего вектора прямой
  Vector direction = Vector(ptr2->getDot1(), ptr2->getDot2());
  //нормализация направляющего вектора
  Vector vector2 = Vector(direction.getX(), direction.getY());
  Vector z = vector2.Normalize();
  // новый вектор 
  Vector vector = Vector(circleCenterPoint.getX() - firstLinePtX, circleCenterPoint.getY() - firstLinePtY);

  //вычисление декартового произведения
  double decartDot = vector.getX()*z.getX() + vector.getY()*z.getY();
  //спроецированный радиус на прямую - точка на прямой
  Point A = Point(firstLinePtX + decartDot*z.getX(), firstLinePtY + decartDot*z.getY());
  // новая прямая с начальной найденной точкой и нормализированным направлением
  Line* str =new Line(A.getX(), A.getY(), z.getX(), z.getY());
  // длина от центра до новой точки на прямой
  double distance = sqrt(pow(A.getX() - circleCenterPoint.getX(), 2) + pow(A.getY() - circleCenterPoint.getY(), 2));
  // длина он начальной точки прямой до найденной
  double rastDot = sqrt(pow(radius, 2) - pow(distance, 2));
  if (distance == 0 || distance == radius)
  {
    // прямая проходит через центр окружности - 2 точки
    if (distance == .0)
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
      double distance = sqrt(pow(parameter.getX() - circleCenterPoint.getX(), 2) + pow(parameter.getY() - circleCenterPoint.getY(), 2));
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
  t = new CalculationResult(COINCIDENCE);
  t->solution = points;
  return t;
}
