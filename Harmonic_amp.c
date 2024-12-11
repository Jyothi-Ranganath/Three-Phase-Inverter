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

////Branch B
// Function to calculate 1st to 5th harmonics amplitudes
void getHarmonicAmplitudes(DDATA *d, int dataSize) {
    for (int n = 1; n <= NUM_HARMONICS; n++) {
        float realPart = 0.0f, imagPart = 0.0f;
        for (int i = 0; i < dataSize; i++) {
            float theta = 2 * PI * n * i / dataSize;
            realPart += d->in_a[i] * cosf(theta);
            imagPart += d->in_a[i] * sinf(theta);
        }

        // Normalize for consistancy and calculate amplitude of harmonics
        realPart /= dataSize;
        imagPart /= dataSize;
        d->Harmonics[n - 1] = sqrtf(realPart * realPart + imagPart * imagPart);
    }
}

// Main function
int main() {
    // Duplicate data for multiple cycles if needed
    int dataSize = DATA_LENGTH * CYCLE;
     

     //branch B
    // Calculate harmonic amplitudes
    getHarmonicAmplitudes(&ddata, dataSize);
    for (int n = 0; n < NUM_HARMONICS; n++) {
        printf("Harmonic %d Amplitude: %.2f V\n", n + 1, ddata.Harmonics[n]);
    }

    return 0;
}
