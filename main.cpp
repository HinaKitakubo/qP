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
   double phi;
   double f;
   double c;
   double cmax;
   double C = 1.0;  //10.
   double P;
   double q;
   double a, s, t, u;
   double x, X;
   double v, V;
   double vmin, vmax;
   double vx, vy, vz;

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
   std::uniform_real_distribution<double> rand_r(0.0,1.0);

   for( i=0; i<n; i++ ){
      a = data[i][7];
      x = nibun(X, a);
      cmax = cmax_dist(a, x, e);

      do{
         q = rand_r(rand_src);
         c = rand_r(rand_src);
         P = cmax_dist(a, 1.0 - q*q, e);
      }while( cmax*c >= P );
         std::cout << data[i][5] << " " << q << " " << P << " " << sqrt(1.0 - x) << " " << cmax << std::endl;
         i++;
      }

   return 0;
}
