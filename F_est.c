#include <stdio.h>
#include <math.h>

// Define constants
#define CYCLE 1
#define DATA_LENGTH 20
#define PI 3.141592653589793
#define NUM_HARMONICS 5

// Input voltage arrays
float Va[] = {
    156.63, 246.59, 294.72, 305.51, 300.66,
    268.03, 204.18, 125.41, 42.954, -48.322,
    -154.08, -243.95, -293.12, -303.09, -297.98,
    -264.13, -202.1, -122.25, -39.893, 51.818
};

float Vb[] = {
    -308.4, -280.19, -240.66, -186.6, -99.744,
    -0.54547, 92.853, 181.46, 262.05, 312.39,
    311.44, 283.76, 245.04, 188.62, 102.16,
    2.9662, -89.395, -176.17, -259.16, -309.96
};

float Vc[] = {
    156.11, 82.694, -21.783, -128.37, -213.06,
    -269.49, -309.58, -313.4, -273.73, -214.81,
    -154.29, -79.64, 24.679, 132.16, 216.63,
    274.14, 311.11, 315.76, 276.27, 216.22
};

typedef struct _DDATA {
    float *in_a;
    float *in_b;
    float *in_c;
    float F_est;
    float Theta_est;
    float Harmonics[NUM_HARMONICS];
    float Ts; // Sampling time (e.g., 0.001 seconds for 1 kHz)
} DDATA;

DDATA ddata = {
    .in_a = Va,
    .in_b = Vb,
    .in_c = Vc,
    .Ts = 0.001
};
 //branch A_fre_est
// Function to estimate frequency and phase angle
void estimateFrequencyAndTheta(DDATA *d, int dataSize) {
    float dAxis = 0.0f, qAxis = 0.0f;
    float nominalFrequency = 50.0f; // Nominal frequency in Hz
    float omega_t = 2 * PI * nominalFrequency * d->Ts;

    // Rotating reference frame transformation
    // Simplifies 3-phase analysis by isolating fundamental components and suppressing high-frequency harmonics
    // Improves accuracy
    for (int i = 0; i < dataSize; i++) {
        float theta = omega_t * i;
        float cosTheta = cosf(theta);
        float sinTheta = sinf(theta);

        dAxis += d->in_a[i] * cosTheta + d->in_b[i] * cosf(theta - 2 * PI / 3) + d->in_c[i] * cosf(theta + 2 * PI / 3);
        qAxis += d->in_a[i] * sinTheta + d->in_b[i] * sinf(theta - 2 * PI / 3) + d->in_c[i] * sinf(theta + 2 * PI / 3);
    }

    // Normalization for consistency irrespective of the data size or cycles used
    dAxis /= dataSize;
    qAxis /= dataSize;

    // Estimate phase angle
    d->Theta_est = atan2f(qAxis, dAxis) * 180 / PI; // Convert to degrees

    // Estimate frequency using zero-crossings
    // Determine the signal's fundamental frequency by counting zero-level transitions 
    //suitable for high speed processing and real time frequency tracking
    int zeroCrossings = 0;
    for (int i = 1; i < dataSize; i++) {
        if ((d->in_a[i - 1] > 0 && d->in_a[i] <= 0) || (d->in_a[i - 1] < 0 && d->in_a[i] >= 0)) {
            zeroCrossings++;
        }
    }
    d->F_est = (float)(zeroCrossings / 2) * (1.0f / (d->Ts * dataSize));
}


// Main function
int main() {
    // Duplicate data for multiple cycles if needed
    int dataSize = DATA_LENGTH * CYCLE;
     // branch A
    // Estimate frequency and phase angle
    estimateFrequencyAndTheta(&ddata, dataSize);
    printf("Estimated Frequency: %.2f Hz\n", ddata.F_est);
    printf("Phase Angle: %.2f degrees\n", ddata.Theta_est);

    return 0;
}
