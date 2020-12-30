#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#include "common_functions.h"

                                    /**< convolution */

float* convolution(float h_n[], float x_n[], int h_len, int x_len, int* y_len)
{
    int count = h_len+x_len-1;
    (*y_len) = count;                           /**< returning length of convolved signal */
    int i,j,h_start,x_start,x_end;
    float *y_n = (float*) calloc(count, sizeof(float));
    for (i=0; i<count; i++)
    {
        x_start = MAX(0,i-h_len+1);
        x_end   = MIN(i+1,x_len);
        h_start = MIN(i,h_len-1);
        for(j=x_start; j<x_end; j++)
        {
            y_n[i] += h_n[h_start--]*x_n[j];
        }
    }
    return y_n;
}


                         /**< DOWN SAMPLING */

        float *downsampling( float x[],int m,size_t length_x)
        {
            int downsamp_counter=length_x;
            float *x_downsampled = (float*) calloc(downsamp_counter, sizeof(float));
            static int w=0;
            for (w=0;m*w<downsamp_counter;w++)
                {
                    x_downsampled[w]=x[m*w];
                }

             return x_downsampled;
        }

                    /**< UP SAMPLING */

        float *upsampling( float x[],int L,size_t length_xu)
        {
            int upsamp_counter=length_xu*L;
            float *x_upsampled = (float*) calloc(upsamp_counter, sizeof(float));
            static int w=0;
            for (w=0;w<upsamp_counter;w++)
                {
                    if (w%L==0)
                    {
                        x_upsampled[w]=x[w/L];
                    }
                    else
                    {
                      x_upsampled[w]=0;
                    }
                }

             return x_upsampled;
        }
