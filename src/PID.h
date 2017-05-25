
#include <uWS/uWS.h>
#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;



  //number of steps
  int n_steps;
  //base number of steps
  int min_n_steps;
  //twiddle afer number of steps
  int num_twiddle_steps;
  //total error
  double err;
  //control coefficients delta
  double dKp;
  double dKd ;
  double dKi;

  //error tolarance
  double tolerance;
  //best error
  double best_err;
  //twiddle index
  int twiddle_index;
  bool is_first_twiddle;

  bool increase_coefficient;


  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Calculate the output.
  */
  double Output();

  /*
  * Twiddle
  */
  void Twiddle();



  void Restart(uWS::WebSocket<uWS::SERVER> ws);
};


#endif /* PID_H */
