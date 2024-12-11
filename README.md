# Three-Phase-Inverter
For a given a set of three-phase voltage sample data, represented as an array of float numbers sampled at a frequency of 1 kHz.

The C-Code consists of two functions with branches 1 and 2 to estimate the 
Frequency(F_est), Phase angle(Theta_est) and Harmonics Amplitude (1 to 5th) respectively . 
For Analysis of the three phase voltage, Rotating reference frame is used as it simplifies the three phase system to d_q frame.
and Zero Crossing is used to improve the accuracy of frequency estimation. 
Zero Crossing technique is preferred for real time tracking of waveforms and is optimal for microcontrller programming. 
Fourier Tranformation is used for the calculation of the amplitude of the harmonics. 
Odd harmonics are comparitively higher than the even harmonics. 

Final Estimated results of the Frequency, Phase angle and the harmonics amplitude (1 to 5) are inlcuded in the read me of each branch.

