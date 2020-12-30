#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#include "common_functions.h"

                                    /**< HBF with (lh-1) samples rejected */

float* half_band_filter(float h_n[], float x_n[], int h_len, int x_len, int* y_len)
{
    int y_orig = h_len+x_len-1;                                          /**< Original length of output */
    int y_trimmed=y_orig-(h_len-1);                                      /**< Trimming (lh-1)/2 samples */
    (*y_len) = y_trimmed;                                                /**< returning length of output */
    int count_start=(h_len-1)/2;
    float y_midterm[y_trimmed];                                          /**< Separately calculate the middle term in convolution and form pairs for symmetric terms */
    memset(y_midterm, 0, sizeof y_midterm);                              /**< Initializing the array to zero */
    float *y_n = (float*) calloc(y_trimmed, sizeof(float));
    float temparr_x[x_len];
    int i,j,p,k,x_start,x_end,h_start;
    int h_middle=(h_len-1)/2;
    float filter_out[x_len];
    memset(filter_out, 0, sizeof filter_out);

    for(k=0;k<x_len;k++)
    {
        temparr_x[k]=x_n[k];                                               /**< Taken x[n] into temparr_x */
    }
    temparr_x[x_len]=0;                                                 /**< Dummy index for all index of x_n which get higher tha (x_len-1) and setting it to zero */
    x_n[-1]=0;                                                          /**< Taking a dummy index  for all index of x_n which gives negative in below loop */
    for (k=0; k < y_trimmed; k++)
    {
        i=k+count_start;                                                /**< Since we have to start with y[k+((h_len-1)/2)] */
        h_start=h_middle;
        x_end=MIN(i,x_len-1);
        y_midterm[k]=h_n[h_middle]*temparr_x[i-h_middle];                   /**< Computed the middle output corresponding to h[19] in 39-tap*/
        for (j=1;j<=h_middle;j=j+2)
            {
                x_start=MAX(-1,i-h_middle-j);
                x_end=MIN(x_len,i-h_middle+j);
                --h_start;
                filter_out[k]+=(h_n[h_start--]*(temparr_x[x_start]+temparr_x[x_end]));  /**< Grouping and calculating */
            }
            y_n[k]+=y_midterm[k]+filter_out[k];                             /**< Adding the middle term after loop */
    }
      return y_n;
      free(y_n);
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


