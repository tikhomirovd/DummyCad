using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tests4
{
    abstract class Curve
    {
        protected Point Point;

        protected Curve(double x, double y)
        {
            Point = new Point(x, y);
        }

        public Point getCurvePoint()
        {
            return Point;
        }


        public abstract Point PointCalcul(int t); // координата в зависимости от параметра 
        public abstract double TangentCalcul(int t); // касательная к кривой
        public abstract bool ClosedCurve(); // является ли кривая замкнутой  
    }
}
