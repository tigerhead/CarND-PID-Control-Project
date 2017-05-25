#include "PID.h"
#include <uWS/uWS.h>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Kd = Kd;
    this->Ki = Ki;
    this->p_error = 0.0;
    this->d_error = 0.0;
    this->i_error = 0.0;
    //this->min_n_steps = 100;
    //this->n_steps = 0;
    //this->err = 0.0
    //number of steps
    this->n_steps = 0;
    //base number of steps
    this->min_n_steps = 100;
    //twiddle afer number of steps
    this->num_twiddle_steps = 300;
    //total error
    this->err =0.;
    //control coefficients delta
    this->dKp = Kp/4.0;
    this->dKd = 1;
    this->dKi = Ki/10.0;

    //error tolarance
    this->tolerance = 0.001;
    //best error
    this->best_err = 99999999.0;

    //twiddle index
    this->twiddle_index = 0;
    this->is_first_twiddle = true;

    this->increase_coefficient = false;
}

void PID::UpdateError(double cte) {

    d_error = cte -  p_error;
    p_error = cte;
    i_error += cte;
    n_steps +=1;
    if(n_steps > min_n_steps){
        err+=cte * cte;
    }


}

double PID::TotalError() {
    double normalized_err = 0.;
    if(n_steps > min_n_steps){
        normalized_err = err/(n_steps - min_n_steps);
    }

    return normalized_err;
}

double PID::Output(){
    return -(Kp * p_error + Kd*d_error + Ki * i_error);

}


void PID::Twiddle(){
    if(n_steps >= num_twiddle_steps){
        n_steps = 0;//reset number of steps
        double sum_dK = dKp + dKi + dKd;
        //total_error = pid.TotalError();
        if(sum_dK > tolerance){//if total error is greater than tolerance, twiddle PID coeffience
            double cur_err = TotalError();
            if(is_first_twiddle){//first twiddle, increase Kp coefficient
                best_err = cur_err;
                Kp += dKp;
                increase_coefficient = false;
                is_first_twiddle = false;
            }else{
                if(err < best_err){//if err reduced, increase corresponding delta
                    best_err = cur_err;
                    if(twiddle_index == 0){
                        dKp *= 1.1;
                    }else if(twiddle_index == 1){
                        dKi *= 1.1;
                    }else{
                        dKd *= 1.1;
                     }
                    //twiddle next coeffience
                    twiddle_index = (twiddle_index + 1) % 3;
                    increase_coefficient = true;
                    if(twiddle_index == 0){
                        Kp += dKp;
                    }else if(twiddle_index == 1){
                        Ki += dKi;
                    }else{
                        Kd += dKd;
                   }
                }else{
                    if(increase_coefficient){//if coefficient increased and error increase, try reduce correspoding coefficent
                        increase_coefficient = false;
                        if(twiddle_index == 0){
                            Kp -= 2*dKp;
                        }else if(twiddle_index == 1){
                            Ki -= 2*dKi;
                        }else{
                            Kd -= 2*dKd;
                       }
                  }else{//either increase or decrease by delta, error increased, reset coefficience and reduce delta
                        increase_coefficient = true;
                        if(twiddle_index == 0){
                            Kp += dKp;
                            dKp *= 0.9;

                        }else if(twiddle_index == 1){
                            Ki += dKi;
                            dKi *=0.9;
                        }else{
                            Kd += dKd;
                            dKd *=0.9;
                       }

                        //twiddle next coeffience
                        twiddle_index = (twiddle_index + 1) % 3;
                        increase_coefficient = true;
                        if(twiddle_index == 0){
                            Kp += dKp;
                        }else if(twiddle_index == 1){
                            Ki += dKi;
                        }else{
                            Kd += dKd;
                       }


                   }
                }
            }

        }else
            return;

        n_steps = 0;
        err = 0.0;

        std::cout << "New best Kp: " << Kp << " Kd: " << Kd
        << " Ki: " << Ki << " Error: " << best_err;

    }

}






void PID::Restart(uWS::WebSocket<uWS::SERVER> ws){
  std::string reset_msg = "42[\"reset\",{}]";

  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);

}

