#include "MainClass.hpp"

MainClass::MainClass()
{}

  MainClass::MainClass(int nr_of_particles, double noise, double locking_radius,
                                            double initial_distance, double radius_bias, string save_name )
  {
    N = nr_of_particles;
    M = 1; //number of locked
    eta = noise;
    R = initial_distance;
    r = locking_radius;
    bias = radius_bias;

    //define arrays and vectors
    state = Mat<double>(N+1, 2); //r and phi
    filename = save_name;

    //for saving data
    filename = save_name;

    //random number generator
    std::mt19937 generator (std::clock()); //initialize seed with clock
    std::uniform_real_distribution<double> distribution(-1, 1);
  }

  void MainClass::run()
  {
    for (int i = 1; i < N; i++)
    {
      initial_angle = distribution(generator);
      state(i, 0) = R*cos(initial_angle);
      state(i, 1) = R*sin(initial_angle);

      not_locked = true;
      while (not_locked)
      {
        state(i, 0) += (distribution(generator)-bias*sign(state(i,0)))*eta;
        state(i, 1) += (distribution(generator)-bias*sign(state(i,0)))*eta;

        for (int j = 0; j < M; j++)
        {
          if  (sqrt(pow( state(i,0)*state(i,0) - state(j,0)*state(j,0), 2) + pow( state(i,1)*state(i,1) - state(j,1)*state(j,1), 2)) < r)
          {
            not_locked = false;
            M += 1;
            break;
          }
        }
      }
    }
  }

  void MainClass::write()
  {
    std::ofstream outfile;
    outfile.open("data/"+ filename + ".txt");
    if (!outfile.is_open())
        cout << "Could not open file" << endl;

      else
        {for (int i = 0; i < N; i++)
          {
            outfile << state(i, 0) << " " << state(i, 1) << "\n";
          }
        }
  }

  int MainClass::sign(double x)
{
  return (x > 0) - (x < 0);
}
