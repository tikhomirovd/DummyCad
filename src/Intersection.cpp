// Include self.
#include <Intersection.h>

// Includes from STL.
#include <vector>
#include <memory>
#include <math.h>

// Includes from Core.
#include <Point.h>
#include <Curve.h>
#include <Vector.h>
#include <Line.h>
#include <Circle.h>

static const double M_PI = 3.141592653589793;
static const double EPS = 1.e-10;

//=============================================================================
//function : Intersection
//purpose  : общий интерфейс для методов пересечения
//=============================================================================
std::shared_ptr<CalculationResult> Intersections::Intersection(std::shared_ptr<Curve> ptr1, std::shared_ptr<Curve> ptr2)
{
  std::vector<Point> result;

  std::shared_ptr<Line> linePtr1 = std::dynamic_pointer_cast<Line>(ptr1);
  std::shared_ptr<Line> linePtr2 = std::dynamic_pointer_cast<Line>(ptr2);
  std::shared_ptr<Circle> circlePtr1 = std::dynamic_pointer_cast<Circle>(ptr1);
  std::shared_ptr<Circle> circlePtr2 = std::dynamic_pointer_cast<Circle>(ptr2);

  if (linePtr1 && linePtr2)
  {
    return SolveLineLine(linePtr1, linePtr2);
  }
  else if (linePtr1 && circlePtr2)
  {
    return SolveCircleLine(circlePtr2, linePtr1);
  }
  else if (circlePtr1 && linePtr2)
  {
    return SolveCircleLine(circlePtr1, linePtr2);
  }
  else if (circlePtr1 && circlePtr2)
  {
    return SolveCircleCircle(circlePtr1, circlePtr2);
  }
  else
  {
    std::shared_ptr<CalculationResult> t(new CalculationResult);
    t->type = UNSUPPORTED_CURVE;
    return t;
  }
}

//=============================================================================
//function : SolveLineLine
//purpose  : Реализация метода - найти точку пересечения 2 прямых
//=============================================================================
std::shared_ptr<CalculationResult> Intersections::SolveLineLine(std::shared_ptr<Line> ptr1, std::shared_ptr<Line> ptr2)
{
  std::vector<Point> point;
  Point firstLinePoint = ptr1->getCurvePoint();
  /// Получение направляющего вектора первой прямой
  Vector direction1 = ptr1->getDirection();
  Point secondLinePoint = ptr2->getCurvePoint();
  /// Получение направляющего вектора второй прямой
  Vector direction2 = ptr2->getDirection();
  /// Ищем детерминанты
  double determinant1 = direction2.getX() - direction1.getX();
  double determinant2 = direction2.getY() - direction1.getY();

  /// Решаем систему y-p2*t=y0 ; y-p21*t=y01; determinant1 = 1*(-p21)-(-p2)*1
  if (fabs(determinant1) < EPS || fabs(determinant2) < EPS)
  {
    if (firstLinePoint.distance(secondLinePoint) < pow(EPS, 2) && (direction1.summ(direction2)).getSquaredNorm() < pow(EPS, 2))
    {
      std::shared_ptr<CalculationResult> t(new CalculationResult);
      t->type = COINCIDENCE;
      return t;
    }
    std::shared_ptr<CalculationResult> t(new CalculationResult);
    t->type = NO_INTERSECTION;
    return t;
  }
  else
  {
    /// Расчитываем координаты точки пересечения для двух линий через определители матрицы 
    point.push_back(Point((firstLinePoint.getX() * (direction2.getX()) - (direction1.getX() * secondLinePoint.getX())) / determinant1,
      (firstLinePoint.getY()*direction1.getX() - direction1.getY()* secondLinePoint.getY()) / determinant2));
    std::shared_ptr<CalculationResult> t(new CalculationResult);
    t->type = SOLUTION;
    t->solution = point;
    return t;
  }
}

//=============================================================================
//function : SolveCircleCircle
//purpose  : Реализация метода - найти точку/и пересечения двух окружностей
//=============================================================================
std::shared_ptr<CalculationResult> Intersections::SolveCircleCircle(std::shared_ptr<Circle> ptr1, std::shared_ptr<Circle> ptr2)
{
  std::vector<Point> points;
  Point firstCenterPoint = ptr1->getCurvePoint();
  Point secondCenterPoint = ptr2->getCurvePoint();
  /// Получение радиусов
  double firstRadius = ptr1->getRadius();
  double secondRadius = ptr2->getRadius();
  /// Создаем переменные для суммы и разности радиусов
  double sumRadius = firstRadius + secondRadius;
  double deltaX = fabs(firstCenterPoint.getX() - secondCenterPoint.getX());
  double deltaY = fabs(firstCenterPoint.getY() - secondCenterPoint.getY());
  double deltaR = fabs(firstRadius - secondRadius);
  /// Расстояние между центрами окружностей
  double distance = sqrt(pow(deltaX, 2) + pow((deltaY), 2));
  /// Исключение концентрических окружностей (окружности с одинаковыми координатами центра и радиусами)
  if (deltaX + deltaY + deltaR < EPS)
  {
    std::shared_ptr<CalculationResult> t(new CalculationResult);
    t->type = COINCIDENCE;
    return t;
  }
  else if (
    /// В одной точке с разным радиусом
    (deltaX + deltaY < EPS && deltaR > EPS) ||
    /// Круг вне круга или круг внутри круга
    (distance > sumRadius + EPS || distance < deltaR - EPS)
    )
  {
    std::shared_ptr<CalculationResult> t(new CalculationResult);
    t->type = NO_INTERSECTION;
    return t;
  }
  else if (fabs(distance - sumRadius) < EPS || fabs(distance - deltaR) < EPS)
  {
    /// 1 решение
    /// Получение среднего значения суммы координат
    double middlePoint1 = (firstCenterPoint.getX() + secondCenterPoint.getX()) / 2.0;
    double middlePoint2 = (firstCenterPoint.getY() + secondCenterPoint.getY()) / 2.0;
    /// Получаем разность координат
    double coordinate1 = firstCenterPoint.getX() - secondCenterPoint.getX();
    double coordinate2 = firstCenterPoint.getY() - secondCenterPoint.getY();
    /// Формирует точку - направление
    Vector vector1(-coordinate1, -coordinate2);
    /// Новая прямая записанная через умный указатель
    std::shared_ptr<Curve> line = std::shared_ptr<Line>(new Line(middlePoint1, middlePoint2, Vector(vector1.getX(), vector1.getY())));
    /// Вычисление точек на прямой, которая пересекает каждую из окружностей
    std::shared_ptr<CalculationResult> points1 = Intersection(line, ptr1);
    std::shared_ptr<CalculationResult> points2 = Intersection(line, ptr2);
    /// Сравнение полученных координат - ищем общую и её записываем в ответ
    if ((points1->solution[0] == points2->solution[0]) || (points1->solution[0] == points2->solution[1]))
    {
      points.push_back(Point(points1->solution[0].getX(), points1->solution[0].getX()));
      std::shared_ptr<CalculationResult> t(new CalculationResult);
      t->type = COINCIDENCE;
      t->solution = points;
      return t;
    }
    if ((points1->solution[1] == points2->solution[1]) || (points1->solution[1] == points2->solution[0]))
    {
      points.push_back(Point(points1->solution[1].getX(), points1->solution[1].getY()));
      std::shared_ptr<CalculationResult> t(new CalculationResult);
      t->type = COINCIDENCE;
      t->solution = points;
      return t;
    }
  }
  else
  {
    /// 2 решения
    /// Получение серединной точки на прямой
    double middlePoint1 = (firstCenterPoint.getX() + secondCenterPoint.getX()) / 2.0;
    double middlePoint2 = (firstCenterPoint.getY() + secondCenterPoint.getY()) / 2.0;
    Point d(middlePoint1, middlePoint2);
    /// Получение разности координат
    double coordinate1 = firstCenterPoint.getX() - secondCenterPoint.getX();
    double coordinate2 = firstCenterPoint.getY() - secondCenterPoint.getY();
    /// Координаты направляющего вектора на первой прямой
    Vector vector1(-coordinate1, -coordinate2);
    /// Координаты направлябщего вектора прямой, через которую будут искаться решения
    Vector vector2(-coordinate2, coordinate1);
    /// Создаем умный указатель на неё и передаем вычисленные значения
    std::shared_ptr<Curve> line = std::shared_ptr<Line>(new Line(middlePoint1, middlePoint2, vector2));
    /// Вычисляем точки пересечения прямой с этими окружностями
    std::shared_ptr<CalculationResult> points1 = Intersection(line, ptr1);
    std::shared_ptr<CalculationResult> points2 = Intersection(line, ptr2);
    /// Добавляем из первой, т.к. точки одинаковы
    points.push_back(Point(points1->solution[0].getX(), points1->solution[0].getY()));
    points.push_back(Point(points1->solution[1].getX(), points1->solution[1].getY()));
    std::shared_ptr<CalculationResult> t(new CalculationResult);
    t->type = COINCIDENCE;
    t->solution = points;
    return t;
  }
};

//=============================================================================
//function : SolveCircleLine
//purpose  : Реализация метода - найти точку/и пересечения прямой и окружности
//=============================================================================
std::shared_ptr<CalculationResult> Intersections::SolveCircleLine(std::shared_ptr<Circle> ptr1, std::shared_ptr<Line> ptr2)
{
  std::vector<Point> points;
  Point circleCenterPoint = ptr1->getCurvePoint();
  /// Получение радиуса
  double radius = ptr1->getRadius();
  /// Получение точек прямой
  Point firstLinePoint = ptr2->getCurvePoint();
  /// Получение направляющего вектора прямой
  Vector direction = ptr2->getDirection();
  /// Нормализация направляющего вектора
  Vector vector2(direction.getX(), direction.getY());
  Vector z = vector2.Normalize();
  /// Новый вектор 
  Vector vector(circleCenterPoint.getX() - firstLinePoint.getX(), circleCenterPoint.getY() - firstLinePoint.getY());
  /// Вычисление декартового произведения
  double decartDot = vector.getX()*z.getX() + vector.getY()*z.getY();
  /// Спроецированный радиус на прямую - точка на прямой
  Point A(firstLinePoint.getX() + decartDot*z.getX(), firstLinePoint.getY() + decartDot*z.getY());
  /// Новая прямая с начальной найденной точкой и нормализированным направлением
  Line str(A.getX(), A.getY(), Vector(z.getX(), z.getY()));
  /// Длина от центра до новой точки на прямой
  double distance = sqrt(pow(A.getX() - circleCenterPoint.getX(), 2) + pow(A.getY() - circleCenterPoint.getY(), 2));
  /// Длина он начальной точки прямой до найденной
  double rastDot = sqrt(pow(radius, 2) - pow(distance, 2));
  /// Прямая проходит через центр окружности - 2 точки
  if (fabs(distance) < EPS)
  {
    Point ty = str.PointCalcul(-radius);
    Point ty2 = str.PointCalcul(+radius);
    points.push_back(Point(ty.getX(), ty.getY()));
    points.push_back(Point(ty2.getX(), ty2.getY()));
    std::shared_ptr<CalculationResult> t(new CalculationResult);
    t->type = COINCIDENCE;
    t->solution = points;
    return t;
  }
  /// Одна точка на прямой       
  else
  {
    if (fabs(distance - radius) < EPS)
    {
      Line str1(firstLinePoint.getX(), firstLinePoint.getY(), Vector(z.getX(), z.getY()));
      Point ty = str1.PointCalcul(decartDot);
      points.push_back(Point(ty.getX(), ty.getY()));
      std::shared_ptr<CalculationResult> t(new CalculationResult);
      t->type = COINCIDENCE;
      t->solution = points;
      return t;
    }
    /// Две точки пересечения
    else
    {
      if (distance < radius + EPS)
      {
        /// Находим координаты на нашей прямой в точке 1
        Point parameter = str.PointCalcul(1);
        /// Ищем точку с найденным параметром
        Point point1 = str.PointCalcul(-rastDot);
        points.push_back(Point(point1.getX(), point1.getY()));
        if (rastDot < radius + EPS)
        {
          Point point2 = str.PointCalcul(rastDot);
          points.push_back(Point(point2.getX(), point2.getY()));
          std::shared_ptr<CalculationResult> t(new CalculationResult);
          t->type = COINCIDENCE;
          t->solution = points;
          return t;
        }
      }
      else
      {
        std::shared_ptr<CalculationResult> t(new CalculationResult);
        t->type = NO_INTERSECTION;
        return t;
      }
    }
  }
};
