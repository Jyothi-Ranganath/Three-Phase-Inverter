# Three-Phase-Inverter
Estimate Frequency (F_est),  Phase angle(Theta_est)  of the three phase voltage signal using rotating reference frame.

For given a set of three-phase voltage sample data, represented as an array of float
numbers, sampled at a frequency of 1 kHz. 
C-language code is built to calculate the following parameters from the given data:
Functions to calculate the Estimated Frequency (F_est) and Phase Angle (Theta_est) are included in the code. 

The function takes the voltage sample data as an input and calculates the estimated.
Rotating reference frame is used to analyse the 3-phase voltage.
frequency (F_est) is estimated using the Zero crossing as it enables high speed processing and focuses on the sign change instead of entire waveform.
Also phase angle (Theta_est) is estimated using the D_axis and Q_axis data. 
Data are normalized to improve the accuracy. 


## Output of the Program

The program calculates and displays the Estimated Frequency and Phase Angle . Below is the output for given data:

```plaintext
Estimated Frequency: 50.00 Hz
Phase Angle: 60.01 degrees
