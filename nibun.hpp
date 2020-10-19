// 2分法で P が最大の時の x(= 1 - q*q) を求める

double p(double X, double a)   // dP(x)/dx の分子を整理した式
{
   double e = 2.939975;
   double t = pow(e, 5.0);
   double B = t * pow(0.5*a*a, -5.0);

   return 18.0*B*X - 14.0*B + 5.0*pow(X, 6.0) - pow(X, 5.0);
}

double nibun(double X, double a)
{
   double x_1, x_2;

   x_1 = 0.0;
   x_2 = 1.0;

   for(int i=0; i<100; i++){   // 2分法
      X = (x_1 + x_2) / 2.0;

      if( p(X,a) == 0 ){ break; }
      if( p(x_1,a) * p(X,a) < 0 ){ x_2 = X; }
      if( p(x_1,a) * p(X,a) > 0 ){ x_1 = X; }
   }

   return X;
}
