#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iomanip>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "dist.hpp"
#include "nibun.hpp"
#include "cmax.hpp"

using namespace std;

/*
typedef struct vxyz{
   double vx;
   double vy;
   double vz;
} VTEX;
*/

int main() {
   std::ifstream stream("./vmax.dat");
   string line;

   double data[1000][8];
   const string delim = " ";
   int row = 0;
   int col;
   int n;
   int i = 0;
   const double PI = acos(-1);
   double f_0 = 0.001958;
   double f_1 = 0.06516;
   double e = 2.939975;
   double v;
   double phi;
   double f;
   double c;
   double cmax;
   double C = 1.0;  //10.
   double P;
   double q;
   double a, s, t, u, x, X;

   while ( getline(stream, line) ) {   //"vmax.dat"を数列として格納する
      col = 0;
      for ( string::size_type spos, epos = 0;
          (spos = line.find_first_not_of(delim, epos)) != string::npos;) {
         string token = line.substr(spos,(epos = line.find_first_of(delim, spos))-spos);
         data[row][col++] = stod(token);
      }
      ++row;
   }

   std::cout << "Enter the number of particles : n = " ;   //粒子数を入力
   std::cin >> n;

   std::mt19937 rand_src(12345);
   std::uniform_real_distribution<> rand_c(0,cmax);   //cの範囲
   std::uniform_real_distribution<> rand_q(0,1);

   while( i < n ){
      q = rand_q(rand_src);
      a = data[i][7];

      f = f_dist(a, q, e);
      v = a * q;
      P = C * v * v * f;

      x = nibun(X, a);               // P(X) = 0 を満たす x を2分法で求める
      cmax = cmax_dist(a, x, e);     // cmax = Pの最大値
      c = rand_c(rand_src);

      if( c < P && P < cmax ){
         std::cout << data[i][5] << " " << q << " " << P << " " << sqrt(1.0 - x) << "  " << cmax << std::endl;
         i++;
      }
   }

   return 0;
}
