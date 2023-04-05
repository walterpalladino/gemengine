
#pragma once

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Initialize_CosSin(void);
double Cos(unsigned int Angle);
double Sin(unsigned int Angle);
double Cos(float Angle);
double Sin(float Angle);

// float   rand0to1(void) { return rand()/(float)RAND_MAX; }
#define rand0to1 (float)(rand() / (float)RAND_MAX)

// #define RANDOM_RANGE(lo, hi) ((lo) + (hi - lo) * rand0to1())
#define RANDOM_RANGE(lo, hi) ((lo) + (hi - lo) * rand0to1)

#define RANDOM_VALUE(value) ((float)value * rand0to1)

#ifndef PI
#define PI 3.141592653
#endif

#define RAD_2_DEG 180.0f / M_PI

#define Abs(a) ((a < 0) ? -a : a)
#define Sgn(a) ((a < 0) ? -1 : 1)
