# CarND-PID-Control-Project
Udacity Self-Driven Car Nanodegree program Term2 Project 4 PID controller

# Reflection

Im my PID controller implementation, PID PID values were determined using initial values which could drive car in simulator on the track approximately and then using the twiddle algorithm to refine. To get a good intial value, I did a series of experiment and manually tune PID intial value until the car could drive on track and twiddle algorithm get chance to run to refine PID value further.

## Initial Values

### P term coefficient Kp

The proportional term produces an output value that is proportional to the current CTE(cross track error) value. So Kp value determine how responsive the contorller is to current CTE. If Kp value is too high, steering value will be too large. The car may drive in zig-zag way. However, if Kp is too small, the car may drive out of track before it can correct CTE.  I started Kp at relatively big number like 2, I could see the car swinged and quickly off the track. Then I tried a relatively small number like 0.05, the car drove slow to one side of the roadd and got off the quick eventually. The I tried the valued in the middle, if the car still swing, I get middle value of current value and the lower bound value. If car drove slowly to one side of track, get the middle value of current and the upper bound like the binary search algorithm until I got a good value.

### I term coefficient Ki

Integral term is proportional to both the magnitude of CTE and the duration of CTE. The integral in a PID controller is the sum of CTE over time and gives the accumulated offset that should have been corrected previously. The I-Value gives the conversion from all accumulated CTE errors to the action (steering angle). As the integral CTE error is simply the sum of all the previous values which are handed approx. every 0.1s, the I-value is expected to be ten times smaller than the P-value, with an order of magnitude of 0.01. This change of the order of magnitude accounts for the normalising time to unit length, as the for the correct integration each summand has to be multiplied with length of the integration time, which is times 0.1.

D-Value

The D-Value gives the conversion from the derivative CTE errors to the action (steering angle). As the derivataive CTE error is approximated by the difference between the last two values which are handed with a difference of approx. 0.1s, the D-value is expected to be ten times bigger than the P-value, with an order of magnitude of 1. This change of the order of magnitude accounts for the normalising time to unit length, as the for the correct derivative the difference has be divided by the length of the integration time, which is times 10.
Final Values

After running the twiddle algorithm the following final values were determined:

    The final P-Value is 0.071769, which is close to the expected order of magnitude of 0.1.
    The final I-Value is 0.00411344, which is a bit smaller than a tenth of the P-value, but within the expected range.
    The final D-Value is 0.974954, which is close to ten times the P-value and as well in the expected range.
