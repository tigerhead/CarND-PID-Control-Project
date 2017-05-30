# CarND-PID-Control-Project

Udacity Self-Driven Car Nanodegree program Term2 Project 4 PID controller

# Reflection

In my PID controller implementation, PID PID values were determined using initial values which could drive car in simulator on the track approximately and then using the twiddle algorithm to refine. To get a good initial value, I did a series of experiment and manually tune PID intial value until the car could drive on track and twiddle algorithm get chance to run to refine PID value further.

## Initial Values

### Proportional term coefficient Kp

The proportional term produces an output value that is proportional to the current CTE(cross track error) value. So Kp value determine how responsive the controller is to current CTE. If Kp value is too high, steering value will be too large. The car may drive in zig-zag way. However, if Kp is too small, the car may drive out of track before it can correct CTE.  I started Kp at relatively big number like 2, I could see the car swinged and quickly off the track. Then I tried a relatively small number like 0.05, the car drove slow to one side of the track and got off the quick eventually. The I tried the valued in the middle, if the car still swing, I get middle value of current value and the lower bound value. If car drove slowly to one side of track, get the middle value of current and the upper bound like the binary search algorithm until I got a good value: 0.15.

### Integral term coefficient Ki

Integral term is proportional to both the magnitude of CTE and the duration of CTE. The integral in a PID controller is the sum of CTE over time and gives the accumulated offset that should have been corrected previously. In theory, The integral term accelerates the movement of the process towards set-point and eliminates the residual steady-state error that occurs with a pure proportional controller. However, since the integral term responds to accumulated errors from the past, it can cause the present value to overshoot the set point value. Ki should be much smaller than Ki, so I set Ki as 0.01 of Kp and manually tuned it to 0.003

### Derivative term coefficent Kd

The derivative term proportional to the slope(derivataive) of CTE over time. Derivative term predicts system behavior and thus improves settling time and stability of controller. In this project, the derivative  CTE  is approximated by the difference between the last two values which are handed with a difference of approx. 0.1s, Kd is expected to be ten times bigger than the Kp, with an order of magnitude of 1. So I set Kd = 10 * Kp .

## Twiddle

After running the twiddle algorithm the following final values were determined: I finally use Kp = 0.2, Ki = 0.04, Kd = 2.5

  
