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

typedef struct xyz{
   double x;
   double y;
   double z;
} VTEX;

int main() {
   std::ifstream stream("./vmax.dat");
   string line;

   int row = 0;
   int col;
   int n;
   int i = 0;
   const double PI = acos(-1);
   double data[1000][8];
   const string delim = " ";
   double f_0 = 0.001958;
   double f_1 = 0.06516;
   double e = 2.939975;
   double f;
   double c;
   double cmax;
   double C = 1.0;  //10.
   double P;
   double q;
   double a, s, t, u;
   double x, X;
   double vel;

   double theta;
   double phi;
   double Z;
   double min_phi = 0.;
   double max_phi = 2.0 * PI;
   double min_Z = -1.0;
   double max_Z = 1.0;

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

   VTEX v[n];
   VTEX V[n];

   std::mt19937 rand_src(12345);
   std::uniform_real_distribution<> rand_r(0.0,1.0);
   std::uniform_real_distribution<> rand_phi(min_phi, max_phi);
   std::uniform_real_distribution<> rand_Z(min_Z, max_Z);

   while( i < n ){
      a = data[i][7];
      x = nibun(X, a);
      cmax = cmax_dist(a, x, e);

      do{
         q = rand_r(rand_src);
         c = rand_r(rand_src);
         P = cmax_dist(a, 1.0 - q*q, e);
      }while( cmax*c >= P );

      vel = a * (1.0 - q*q);     //ここで、条件に合う速度vの絶対値が求まった
                                 //以下で速度vのx, y, z成分を求める
      phi = rand_phi(rand_src);
      Z = rand_Z(rand_src);      //Z=cosθ

      V[n].x = vel * sqrt(1 - Z*Z) * cos(phi);
      V[n].y = vel * sqrt(1 - Z*Z) * sin(phi);
      V[n].z = vel * Z;

      v[n].x = V[n].x;
      v[n].y = V[n].y;
      v[n].z = V[n].z;

      //std::cout << data[i][5] << " " << q << " " << P << " " << sqrt(1.0 - x) << " " << cmax << std::endl;      std::cout << vel << " " << v[n].x << " " << v[n].y << " " << v[n].z << std::endl;
      i++;
   }

   return 0;
}
