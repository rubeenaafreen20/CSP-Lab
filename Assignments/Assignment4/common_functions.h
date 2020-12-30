#ifndef COMMON_FUNCTIONS_1_H_INCLUDED
#define COMMON_FUNCTIONS_1_H_INCLUDED
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))
#define MIN(a,b) (((a)<(b))?(a):(b))

extern float* half_band_filter(float h_n[], float x_n[], int h_len, int x_len, int* y_len);
extern float *downsampling( float x[],int m,size_t length_x);
extern  float *upsampling( float x[],int l,size_t length_xu);
#endif // COMMON_FUNCTIONS_1_H_INCLUDED
