#include "MainClass.hpp"

MainClass::MainClass()
{}

  MainClass::MainClass(int nr_of_particles, double noise, double locking_radius,
                                            double initial_distance, double radius_bias, string save_name )
  {
    N = nr_of_particles;
    eta = noise;
    R = initial_distance;
    r = locking_radius;
    bias = radius_bias;

    //define arrays and vectors
    state = Mat<double>(N+1, 3); //r and phi
    filename = save_name;

    //for saving data
    filename = save_name;

    //random number generator
    std::mt19937 generator (std::clock()); //initialize seed with clock
    std::uniform_real_distribution<double> distribution(-1, 1);
  }

  void MainClass::sircle(int number_of_tries)
  {
    for (int i = 1; i < N; i++)
    {
      initial_angle = 2*pi*distribution(generator);
      state(i, 0) = R*cos(initial_angle);
      state(i, 1) = R*sin(initial_angle);

      not_locked = true;
      for (int j = 0; j < number_of_tries; j++) //number of tries
      {
        state(i, 0) += (distribution(generator)-0.5-bias*sign(state(i,0)))*eta;
        state(i, 1) += (distribution(generator)-0.5-bias*sign(state(i,1)))*eta;

        for (int k = 0; k < i; k++)
        {
          if  (sqrt( (state(i,0)-state(k,0)) * (state(i,0)-state(k,0)) + (state(i,1)-state(k,1)) * (state(i,1)-state(k,1)) )  < r)
          {
            not_locked = false;
            break;
          }
        }
      if (!not_locked)
      {break;}
      }

      if (not_locked)
      {
        state(i,0) = 0;
        state(i,1) = 0;
      }
    }
  }


  void MainClass::sphere(int number_of_tries)
  {
    for (int i = 1; i < N; i++)
    {
      phi   = 2*pi*distribution(generator);
      theta = 2*pi*distribution(generator);
      state(i, 0) = R*cos(phi)*sin(theta);
      state(i, 1) = R*sin(phi)*sin(theta);
      state(i, 2) = R*cos(theta);

      not_locked = true;
      for (int j = 0; j < number_of_tries; j++) //number of tries
      {
        state(i, 0) += (distribution(generator)-0.5-bias*sign(state(i,0)))*eta;
        state(i, 1) += (distribution(generator)-0.5-bias*sign(state(i,1)))*eta;
        state(i, 2) += (distribution(generator)-0.5-bias*sign(state(i,2)))*eta;

        for (int k = 0; k < i; k++)
        {
          if  (sqrt( (state(i,0)-state(k,0)) * (state(i,0)-state(k,0)) + (state(i,1)-state(k,1)) * (state(i,1)-state(k,1)) + (state(i,2)-state(k,2)) * (state(i,2)-state(k,2)) )  < r)
          {
            not_locked = false;
            break;
          }
        }
      if (!not_locked)
      {break;}
      }

      if (not_locked)
      {
        state(i,0) = 0;
        state(i,1) = 0;
        state(i,2) = 0;
      }
    }
  }

  void MainClass::rectangle(int number_of_tries)
  {
    for (int i = 1; i < N; i++)
    {
      state(i, 0) = distribution(generator);
      state(i, 1) = R;
      state(i, 2) = 0;

      not_locked = true;
      for (int j = 0; j < number_of_tries; j++) //number of tries
      {
        state(i, 0) += (distribution(generator)-0.5)*eta;
        state(i, 1) += (distribution(generator)-0.5-bias*sign(state(i,1)))*eta;

        for (int k = 0; k < i; k++)
        {
          if  (sqrt( (state(i,0)-state(k,0)) * (state(i,0)-state(k,0)) + (state(i,1)-state(k,1)) * (state(i,1)-state(k,1)) )  < r   |  state(i,1) < r)
          {
            not_locked = false;
            break;
          }
        }
      if (!not_locked)
      {break;}
      }

      if (not_locked)
      {
        state(i,0) = 0;
        state(i,1) = 0;
        state(i,2) = 0;
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
            outfile << state(i, 0) << " " << state(i, 1) << " " << state(i, 2) << "\n";
          }
        }
  }

  int MainClass::sign(double x)
{
  return (x > 0) - (x < 0);
}
