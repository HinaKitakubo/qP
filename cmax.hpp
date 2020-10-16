double cmax_dist(double a, double x, double e)
{
      double s = 0.5 * a * a * x;
      double t = pow(e,5.0);
      double u = pow(s, 5.0);

      return a*a * (1.0 - x) * pow(s, 7.0/2.0) * pow(t+u, -13./20.);
}
~ 
