#ifndef MAINCLASS
#define MAINCLASS

#include <iostream>
#include <cmath>
#include <armadillo>
#include <cstdio>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace arma;

class MainClass
{
public:
  int N;
  int M;
  bool not_locked;
  double eta;
  double initial_distance;
  double R;
  double r;
  double bias;
  double initial_angle;

  double pi = acos(-1.0);

  //for writing to file
  string filename;
  int data_lines;

  //positions
  Mat<double> state;

  //random number generators
  std::mt19937 generator;
  std::uniform_real_distribution<double> distribution;

  MainClass();
  MainClass(int nr_of_particles, double rnoise, double locking_radius,
                                             double initial_distance, double radius_bias, string save_name);

  void run();
  void write();
  int sign(double x);
};

#endif
