// 2分法で求めた x の値から P が最大値（＝cmax）を求める

double cmax_dist(double a, double x, double e)
{
      double t = pow(e, 5.0);
      double S = 0.5 * a * a * x;
      double U = pow(S, 5.0);

      return ( a*a * (1.0 - x) * pow(S, 7.0/2.0) * pow(t+U, -13./20.) ) / ( a*a * pow(0.5*a*a, 1.0/4.0) );
}
