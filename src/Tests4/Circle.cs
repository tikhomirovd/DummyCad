using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tests4
{
    class Circle : Curve
    {
        double Radius;

       public Circle(int x, int y, double radius) : base(x, y)
        {
            Radius = radius;
        }

        public double getRadius()
        {
            return Radius;
        }

        public override bool ClosedCurve()
        {
            return true;
        }

        public override Point PointCalcul(int t)
        {
            return new Point(Radius * Math.Cos(t),
                Radius * Math.Sin(t));
        }

        public override double TangentCalcul(int t)
        {
            Point pt = PointCalcul(t);
            double f = -(Math.Cos(t) / Math.Sin(t));
            // общий вид касательной
            // y-y0=f'(x-x0)
            Console.WriteLine("y "+(-pt.getY())+" = "+f+" (x"+-(-pt.getX())+" )");
            return 0;
        }
    }
}
