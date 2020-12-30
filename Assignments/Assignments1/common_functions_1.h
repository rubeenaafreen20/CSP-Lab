#ifndef COMMON_FUNCTIONS_1_H_INCLUDED
#define COMMON_FUNCTIONS_1_H_INCLUDED

extern float *convolution( float x_n[],float h_n[],size_t x_len, size_t h_len,int *y_len);
extern float *correlation( float x_n[],float h_n[],size_t x_len,size_t h_len,int *y_len);
extern float *downsampling( float x[],int m,size_t length_x);

#endif // COMMON_FUNCTIONS_1_H_INCLUDED
