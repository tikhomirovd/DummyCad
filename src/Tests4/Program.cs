using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tests4
{
    class Program
    {
        // пересечение двух прямых
        public static List<Point> Intersection(Straight first, Straight second)
        {
            List<Point> points = new List<Point>();

            Point firstLinePoint = first.getCurvePoint();
            // получение координат первой прямой
            double firstLinePtX = firstLinePoint.getX();
            double firstLinePtY = firstLinePoint.getY();
            // получение направляющего вектора первой прямой
            double firstP1 = first.getP1();
            double firstP2 = first.getP2();

            Point secondLinePoint = second.getCurvePoint();
            //получение координат второй прямой
            double secondLinePtX = secondLinePoint.getX();
            double secondLinePtY = secondLinePoint.getY();
            // получение направляющего вектора второй прямой
            double secondP1 = second.getP1();
            double secondP2 = second.getP2();

            // nullone - x0,y0; nulltwo - x01,y01; vector1 - p1,p2; vector2 - p11,p21
            // x = x01+p11*t ; y = y01+p21*t
            // уравнения вида : x=x0+p1*t ; y=y0+p2*t, где x0,yo - точки на прямой, а p1,p2 - направляющий вектор

            // преобразовывает в вид : x-p1*t=x0 ; y-p2*t=y0 
            // решаем систему x-p1*t=x0 ; x-p11*t=x01; determinant1 = 1*(-p11)-(-p1)*1;

            double determinant1 = -secondP1 - (-firstP1);
            // решаем систему y-p2*t=y0 ; y-p21*t=y01; determinant1 = 1*(-p21)-(-p2)*1
            double determinant2 = -secondP2 - (-firstP2);

            if (determinant1 != 0 && determinant2 != 0)
            {
                points.Add(new Point((firstLinePtX * (-secondP1) - (-firstP1 * secondLinePtX)) / determinant1,
                    (secondLinePtY - firstLinePtY) / determinant2));
            }
            return points;
        }

        // пересечение двух окружностей
        public static List<Point> Intersection(Circle first, Circle second)
        {
            List<Point> points = new List<Point>();

            Point firstCenterPoint = first.getCurvePoint();
            // получение координат первой окружности 
            double firstX = firstCenterPoint.getX();
            double firstY = firstCenterPoint.getY();

            Point secondCenterPoint = second.getCurvePoint();
            // получение координат второй окружности 
            double secondX = secondCenterPoint.getX();
            double secondY = secondCenterPoint.getY();
            //получение радиусов
            double firstRadius = first.getRadius();
            double secondRadius = second.getRadius();
            //расстояние между центрами окружностей
            double distance = Math.Sqrt(Math.Pow((firstX - secondX), 2) + Math.Pow((firstY - secondY), 2));
            if (distance <= firstRadius + secondRadius)
            {
                // Первая точка
                points.Add(new Point(Math.Acos(((secondX - firstX) / (firstRadius - secondRadius))),
                   Math.Asin((secondY - firstY) / (firstRadius - secondRadius))));

                //Вторая точка
                if (distance < (firstRadius + secondRadius))
                {
                    points.Add(new Point(Math.PI - Math.Acos(((secondX - firstX) / (firstRadius - secondRadius))),
                        Math.PI - Math.Asin((secondY - firstY) / (firstRadius - secondRadius))));
                }
            }
            return points;
        }
        // пересечение прямой и окружности
        public static List<Point> Intersection(Straight straight, Circle circle)
        {
            List<Point> points = new List<Point>();

            Point circleCenterPoint = circle.getCurvePoint();
            //получение координат центра окружности 
            double firstcirclePtX = circleCenterPoint.getX();
            double firstcirclePtY = circleCenterPoint.getY();
            //получение радиуса
            double radius = circle.getRadius();

            Point firstLinePoint = straight.getCurvePoint();
            //получение координат прямой
            double firstLinePtX = firstLinePoint.getX();
            double firstLinePtY = firstLinePoint.getY();
            //получение направляющего вектора прямой
            double firstP1 = straight.getP1();
            double firstP2 = straight.getP2();

            Point zeroPoint = straight.PointCalcul(0); // случайная точка на прямой 1
            Point randomPoint = straight.PointCalcul(new Random().Next(1,10)); // случайная точка на прямой 2
            // получение центральной точки на прямой 
            Point middle = new Point(zeroPoint.getX() - randomPoint.getX(), zeroPoint.getY() - randomPoint.getY());
            //расстояние от центра окружности до центральной точки
            double distance = Math.Abs(middle.getY() * firstcirclePtX + middle.getX() * firstcirclePtY + 
                (zeroPoint.getY() * randomPoint.getX() - randomPoint.getY() * zeroPoint.getX())) / 
                Math.Sqrt(Math.Pow(middle.getY(), 2) + Math.Pow(middle.getX(), 2));
            // расчет точек 
            if (distance <= radius)
            {
                points.Add(new Point(2 * Math.Asin(distance / radius), 2 * Math.Acos(distance / radius)));
                if (distance < radius)
                {
                    points.Add(new Point((2 * Math.Asin(distance / radius)-distance), (2 * Math.Acos(distance / radius)-distance)));
                }
            }

            return points;
        }


        public static void printIntersectionPoints(string intersectionType, List<Point> points)
        {
            if (points.Count() == 0)
            {
                Console.WriteLine("Точки пересечения для обьектов " + intersectionType + " не найдены");
                return;
            }

            Console.WriteLine("Точки пересечения для обьектов " + intersectionType + ":");
            foreach (Point pt in points)
            {
                Console.WriteLine("[" + pt.getX() + ", " + pt.getY() + "]");
            }
            Console.WriteLine();
        }

        static void Main(string[] args)
        {
            Straight firstStraight = new Straight(5, 6, 7, 8);
            Straight secondStraight = new Straight(1, 2, 3, 4);

            firstStraight.ClosedCurve();
            firstStraight.PointCalcul(5);
            firstStraight.TangentCalcul(5);

            Circle firstCircle = new Circle(5, 8, 3);
            Circle secondCircle = new Circle(3, 7, 13);

            firstCircle.ClosedCurve();
            firstCircle.PointCalcul(8);
            firstCircle.TangentCalcul(8);

            printIntersectionPoints("Прямая и прямая" ,Intersection(firstStraight, secondStraight));
            printIntersectionPoints("Окружность и окружность", Intersection(firstCircle, secondCircle));
            printIntersectionPoints("Прямая и окружность", Intersection(firstStraight, secondCircle));
            
            Console.ReadKey();
        }
    }
}
