using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tests4
{
    class Straight : Curve
    {
        double p1, p2;

        public Straight(double x, double y, double p1, double p2) : base(x, y)
        {
            this.p1 = p1;
            this.p2 = p2;
        }

        public double getP1()
        {
            return p1;
        }

        public double getP2()
        {
            return p2;
        }

        public override bool ClosedCurve()
        {
            return false;
        }

        public override Point PointCalcul(int t)
        {
            double x0 = Point.getX() - p1 * t;
            double y0 = Point.getY() - p2 * t;
            return new Point(x0, y0);
        }

        public override double TangentCalcul(int t)
        {
            Console.WriteLine("сама себе касательная");
            return 0;
        }
    }
}
