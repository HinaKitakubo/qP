double f_dist(double a, double q, double e)
{

      double s = 0.5 * a * a *(1.0 - q*q);
      double t = pow(e,5.0);
      double u = pow(s, 5.0);

      return pow(s, 7.0/2.0) * pow(t+u, -13./20.);   //f_0 を掛けていたのを消した
}
