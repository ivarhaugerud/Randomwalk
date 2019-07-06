#include <iostream>
#include <cmath>
#include <armadillo>
#include <cstdio>
#include <random>
#include <ctime>
#include <string>
#include <typeinfo>

#include "MainClass.hpp"

using namespace std;
using namespace arma;

//runs for a single configuration which can be specified in command line
//used for example for making plot of spins with black down and white up

int main(int argc, char const *argv[])
  {
    int number_of_particles = atoi(argv[1]);
    double        noise     = atof(argv[2]);
    double locking_radius   = atof(argv[3]);
    double initial_distance = atof(argv[4]);
    double radius_bias      = atof(argv[5]);

    string save_name  = "mysen_2_sircle";

    MainClass virre(number_of_particles, noise, locking_radius, initial_distance, radius_bias, save_name);

    virre.sircle(10000);
    virre.write();

    return 0;
  }
